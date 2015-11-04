fluent cpa_clog(cpa_t0);
fluent cpa_defused(cpa_b0);
fluent cpa_in(cpa_p0,cpa_b0);
fluent cpa_in(cpa_p1,cpa_b0);
fluent cpa_in(cpa_p2,cpa_b0);
fluent cpa_in(cpa_p3,cpa_b0);
fluent cpa_in(cpa_p4,cpa_b0);
fluent cpa_in(cpa_p5,cpa_b0);
fluent cpa_in(cpa_p6,cpa_b0);
fluent cpa_in(cpa_p7,cpa_b0);
fluent cpa_in(cpa_p8,cpa_b0);
fluent cpa_in(cpa_p9,cpa_b0);

%% actions ------ 

action cpa_flush(cpa_t0);
action cpa_sensep(cpa_p0,cpa_b0);
action cpa_sensep(cpa_p1,cpa_b0);
action cpa_sensep(cpa_p2,cpa_b0);
action cpa_sensep(cpa_p3,cpa_b0);
action cpa_sensep(cpa_p4,cpa_b0);
action cpa_sensep(cpa_p5,cpa_b0);
action cpa_sensep(cpa_p6,cpa_b0);
action cpa_sensep(cpa_p7,cpa_b0);
action cpa_sensep(cpa_p8,cpa_b0);
action cpa_sensep(cpa_p9,cpa_b0);
action cpa_dunk(cpa_p0,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p1,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p2,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p3,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p4,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p5,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p6,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p7,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p8,cpa_b0,cpa_t0);
action cpa_dunk(cpa_p9,cpa_b0,cpa_t0);

%% executable ------ 

executable cpa_dunk(cpa_p0,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p0,cpa_b0);
executable cpa_dunk(cpa_p1,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p1,cpa_b0);
executable cpa_dunk(cpa_p2,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p2,cpa_b0);
executable cpa_dunk(cpa_p3,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p3,cpa_b0);
executable cpa_dunk(cpa_p4,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p4,cpa_b0);
executable cpa_dunk(cpa_p5,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p5,cpa_b0);
executable cpa_dunk(cpa_p6,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p6,cpa_b0);
executable cpa_dunk(cpa_p7,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p7,cpa_b0);
executable cpa_dunk(cpa_p8,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p8,cpa_b0);
executable cpa_dunk(cpa_p9,cpa_b0,cpa_t0) if  -cpa_clog(cpa_t0), cpa_in(cpa_p9,cpa_b0);

%% effects ------ 

cpa_flush(cpa_t0) causes  -cpa_clog(cpa_t0);
cpa_sensep(cpa_p0,cpa_b0) causes  cpa_in(cpa_p0,cpa_b0);
cpa_sensep(cpa_p1,cpa_b0) causes  cpa_in(cpa_p1,cpa_b0);
cpa_sensep(cpa_p2,cpa_b0) causes  cpa_in(cpa_p2,cpa_b0);
cpa_sensep(cpa_p3,cpa_b0) causes  cpa_in(cpa_p3,cpa_b0);
cpa_sensep(cpa_p4,cpa_b0) causes  cpa_in(cpa_p4,cpa_b0);
cpa_sensep(cpa_p5,cpa_b0) causes  cpa_in(cpa_p5,cpa_b0);
cpa_sensep(cpa_p6,cpa_b0) causes  cpa_in(cpa_p6,cpa_b0);
cpa_sensep(cpa_p7,cpa_b0) causes  cpa_in(cpa_p7,cpa_b0);
cpa_sensep(cpa_p8,cpa_b0) causes  cpa_in(cpa_p8,cpa_b0);
cpa_sensep(cpa_p9,cpa_b0) causes  cpa_in(cpa_p9,cpa_b0);
cpa_dunk(cpa_p0,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p1,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p2,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p3,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p4,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p5,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p6,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p7,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p8,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);
cpa_dunk(cpa_p9,cpa_b0,cpa_t0) causes  cpa_defused(cpa_b0), cpa_clog(cpa_t0);

%% initial state ------ 

initially ( cpa_in(cpa_p0,cpa_b0) , -cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0) ) | ( cpa_in(cpa_p1,cpa_b0) , -cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p2,cpa_b0) , -cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p3,cpa_b0) , -cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p4,cpa_b0) , -cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p5,cpa_b0) , -cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p6,cpa_b0) , -cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p7,cpa_b0) , -cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p8,cpa_b0) , -cpa_in(cpa_p9,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) ) | ( cpa_in(cpa_p9,cpa_b0) , -cpa_in(cpa_p8,cpa_b0),-cpa_in(cpa_p7,cpa_b0),-cpa_in(cpa_p6,cpa_b0),-cpa_in(cpa_p5,cpa_b0),-cpa_in(cpa_p4,cpa_b0),-cpa_in(cpa_p3,cpa_b0),-cpa_in(cpa_p2,cpa_b0),-cpa_in(cpa_p1,cpa_b0),-cpa_in(cpa_p0,cpa_b0) );

%% goal state ---------- 
goal   cpa_defused(cpa_b0);
