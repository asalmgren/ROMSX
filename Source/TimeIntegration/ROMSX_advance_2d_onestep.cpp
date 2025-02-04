#include <ROMSX.H>

using namespace amrex;

// advance a single level one 2D step
void ROMSX::advance_2d_onestep (int lev, Real /*dt_lev*/, Real dtfast_lev, int my_iif, int nfast_counter)
{
    MultiFab& U_new = *xvel_new[lev];
    MultiFab& V_new = *yvel_new[lev];

    const int ncomp = 1;

    MultiFab mf_u(U_new, amrex::make_alias, 0, 1);
    MultiFab mf_v(V_new, amrex::make_alias, 0, 1);

    bool first_2d_step=(my_iif==0);
    //Predictor
    bool predictor_2d_step=true;
    int next_indx1 = 0;
    advance_2d(lev, mf_u, mf_v, vec_rhoS[lev], vec_rhoA[lev], vec_ru[lev], vec_rv[lev],
               vec_rufrc[lev], vec_rvfrc[lev],
               vec_Zt_avg1[lev],
               vec_DU_avg1[lev], vec_DU_avg2[lev],
               vec_DV_avg1[lev], vec_DV_avg2[lev],
               vec_rubar[lev], vec_rvbar[lev], vec_rzeta[lev],
                vec_ubar[lev],  vec_vbar[lev],  vec_zeta[lev],
               vec_hOfTheConfusingName[lev], vec_visc2_p[lev], vec_visc2_r[lev],
               ncomp, dtfast_lev, predictor_2d_step, first_2d_step, my_iif, next_indx1);

    //Corrector. Skip it on last fast step
    predictor_2d_step=false;
    if (my_iif < nfast_counter - 1) {
        advance_2d(lev, mf_u, mf_v, vec_rhoS[lev], vec_rhoA[lev], vec_ru[lev], vec_rv[lev],
               vec_rufrc[lev], vec_rvfrc[lev],
               vec_Zt_avg1[lev],
               vec_DU_avg1[lev], vec_DU_avg2[lev],
               vec_DV_avg1[lev], vec_DV_avg2[lev],
               vec_rubar[lev], vec_rvbar[lev], vec_rzeta[lev],
                vec_ubar[lev],  vec_vbar[lev],  vec_zeta[lev],
               vec_hOfTheConfusingName[lev], vec_visc2_p[lev], vec_visc2_r[lev],
               ncomp, dtfast_lev, predictor_2d_step, first_2d_step, my_iif, next_indx1);
    }
}
