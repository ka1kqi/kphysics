#include "all_includes.h"

#ifdef _OPENMP
#include <omp.h>
#endif

class PhotonEngine {
public:
    PhotonEngine(int photons,int threads)
        : Nphotons(photons), nThreads(threads) {}

    bool loadVolumeFromPGM(const std::string& path,int Nz,double dx,double dy,double dz,
                           double mu_a_min,double mu_a_max,
                           double mu_s_min,double mu_s_max,double g_aniso){
        Image im;
        if(!load_pgm(path,im)) return false;
        Nx=im.w; Ny=im.h; this->Nz=Nz;
        this->dx=dx; this->dy=dy; this->dz=dz;
        volume.resize((size_t)Nx*Ny*Nz);
        auto at=[&](int x,int y,int z)->Material&{return volume[x+Nx*(y+Ny*z)];};
        mu_star=0;
        for(int z=0;z<Nz;z++)
            for(int y=0;y<Ny;y++)
                for(int x=0;x<Nx;x++){
                    double ggray=im.pix[x+im.w*y]/255.0;
                    double mu_a=mu_a_min+ggray*(mu_a_max-mu_a_min);
                    double mu_s=mu_s_min+ggray*(mu_s_max-mu_s_min);
                    at(x,y,z)={(float)mu_a,(float)mu_s,(float)g_aniso};
                    mu_star=std::max(mu_star,mu_a+mu_s);
                }
        absorb.assign((size_t)Nx*Ny*Nz,0.0);
        return true;
    }

    void run(){
        double Lx=Nx*dx, Ly=Ny*dy, Lz=Nz*dz;
        auto in_bounds=[&](const Vec3& x)->bool{
            return x.x>=0 && x.x<Lx && x.y>=0 && x.y<Ly && x.z>=0 && x.z<Lz;
        };
        auto voxel_idx=[&](const Vec3& x)->std::array<int,3>{
            int ix=std::clamp((int)std::floor(x.x/dx),0,Nx-1);
            int iy=std::clamp((int)std::floor(x.y/dy),0,Ny-1);
            int iz=std::clamp((int)std::floor(x.z/dz),0,Nz-1);
            return {ix,iy,iz};
        };

        int threadsToUse = 1;
        #ifdef _OPENMP
        threadsToUse = nThreads;
        #endif

        #ifdef _OPENMP
        #pragma omp parallel num_threads(threadsToUse)
        #endif
        {
            unsigned int tid = 0;
        #ifdef _OPENMP
            tid = omp_get_thread_num();
        #endif
            std::random_device rd;
            std::mt19937_64 rng(rd() + tid);
            std::uniform_real_distribution<double> U(0.0,1.0);
            std::vector<double> absorb_local(absorb.size(),0.0);
            double R=0,T=0;

            long long photonsPerThread = Nphotons/threadsToUse + 1;
            for(long long p=0;p<photonsPerThread;p++){
                Vec3 x{0.5*Lx,0.5*Ly,1e-12};
                Vec3 w{0,0,1};
                while(true){
                    double s=-std::log(std::max(1e-12,U(rng)))/mu_star;
                    Vec3 x_new=x+w*s;
                    if(!in_bounds(x_new)){
                        if(w.z<0) R+=1; else T+=1;
                        break;
                    }
                    x=x_new;
                    auto [ix,iy,iz]=voxel_idx(x);
                    const Material& m=volume[ix+Nx*(iy+Ny*iz)];
                    double mu_t=m.mu_a+m.mu_s;
                    if(U(rng)<mu_t/mu_star){
                        if(U(rng)<m.mu_a/mu_t){
                            absorb_local[ix+Nx*(iy+Ny*iz)]+=1;
                            break;
                        } else {
                            w=sample_HG(w,m.g,rng);
                        }
                    }
                }
            }

        #ifdef _OPENMP
        #pragma omp critical
        #endif
            {
                for(size_t i=0;i<absorb.size();i++) 
                    absorb[i]+=absorb_local[i];
                R_total+=R; T_total+=T;
            }
        }
    }
    void writeAbsorption2D(const std::string& csv,const std::string& pgm){
        std::vector<double> sum_xy((size_t)Nx*Ny,0.0);
        for(int z=0;z<Nz;z++)
            for(int y=0;y<Ny;y++)
                for(int x=0;x<Nx;x++)
                    sum_xy[x+Nx*y]+=absorb[x+Nx*(y+Ny*z)];
        // CSV
        std::ofstream out(csv);
        for(int y=0;y<Ny;y++){
            for(int x=0;x<Nx;x++){
                if(x) out<<",";
                out<<sum_xy[x+Nx*y];
            } out<<"\n";
        }
        // PGM
        double mx=*std::max_element(sum_xy.begin(),sum_xy.end());
        std::vector<uint8_t> img(Nx*Ny,0);
        if(mx>0) for(size_t i=0;i<sum_xy.size();i++)
            img[i]=(uint8_t)std::round(255*sum_xy[i]/mx);
        std::ofstream outpgm(pgm,std::ios::binary);
        outpgm<<"P5\n"<<Nx<<" "<<Ny<<"\n255\n";
        outpgm.write((char*)img.data(),img.size());
    }

    void printStats(){
        double A_total=std::accumulate(absorb.begin(),absorb.end(),0.0);
        double total=R_total+T_total+A_total;
        std::cout<<"Reflected = "<<R_total/total<<"\n";
        std::cout<<"Transmitted = "<<T_total/total<<"\n";
        std::cout<<"Absorbed = "<<A_total/total<<"\n";
    }

private:
    int Nx=0,Ny=0,Nz=0;
    double dx=1e-3,dy=1e-3,dz=1e-3;
    int Nphotons, nThreads;
    std::vector<Material> volume;
    std::vector<double> absorb;
    double mu_star=0;
    double R_total=0,T_total=0;
};

