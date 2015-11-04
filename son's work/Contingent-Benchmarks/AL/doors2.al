fluent cpa_at(cpa_p1_1);
fluent cpa_at(cpa_p1_2);
fluent cpa_at(cpa_p2_1);
fluent cpa_at(cpa_p2_2);
fluent cpa_opened(cpa_p1_2);
fluent cpa_opened(cpa_p2_1);
%fluent cpa_opened(cpa_p1_1);
%fluent cpa_opened(cpa_p2_2);

%% actions ------ 

action cpa_move(cpa_p1_1,cpa_p1_2);
action cpa_move(cpa_p1_1,cpa_p2_1);
action cpa_move(cpa_p1_2,cpa_p1_1);
action cpa_move(cpa_p1_2,cpa_p2_2);
action cpa_move(cpa_p2_1,cpa_p1_1);
action cpa_move(cpa_p2_1,cpa_p2_2);
action cpa_move(cpa_p2_2,cpa_p1_2);
action cpa_move(cpa_p2_2,cpa_p2_1);
action cpa_sense_door(cpa_p1_1,cpa_p1_2);
action cpa_sense_door(cpa_p1_1,cpa_p2_1);
%action cpa_sense_door(cpa_p1_2,cpa_p1_1);
%action cpa_sense_door(cpa_p1_2,cpa_p2_2);
%action cpa_sense_door(cpa_p2_1,cpa_p1_1);
%action cpa_sense_door(cpa_p2_1,cpa_p2_2);
action cpa_sense_door(cpa_p2_2,cpa_p1_2);
action cpa_sense_door(cpa_p2_2,cpa_p2_1);

%% executable ------ 

executable cpa_move(cpa_p1_1,cpa_p1_2) if  cpa_at(cpa_p1_1), cpa_opened(cpa_p1_2);
executable cpa_move(cpa_p1_1,cpa_p2_1) if  cpa_at(cpa_p1_1), cpa_opened(cpa_p2_1);
executable cpa_move(cpa_p1_2,cpa_p1_1) if  cpa_at(cpa_p1_2);
executable cpa_move(cpa_p1_2,cpa_p2_2) if  cpa_at(cpa_p1_2);
executable cpa_move(cpa_p2_1,cpa_p1_1) if  cpa_at(cpa_p2_1);
executable cpa_move(cpa_p2_1,cpa_p2_2) if  cpa_at(cpa_p2_1);
executable cpa_move(cpa_p2_2,cpa_p1_2) if  cpa_at(cpa_p2_2), cpa_opened(cpa_p1_2);
executable cpa_move(cpa_p2_2,cpa_p2_1) if  cpa_at(cpa_p2_2), cpa_opened(cpa_p2_1);
executable cpa_sense_door(cpa_p1_1,cpa_p1_2) if  cpa_at(cpa_p1_1);
executable cpa_sense_door(cpa_p1_1,cpa_p2_1) if  cpa_at(cpa_p1_1);
%executable cpa_sense_door(cpa_p1_2,cpa_p1_1) if  cpa_at(cpa_p1_2);
%executable cpa_sense_door(cpa_p1_2,cpa_p2_2) if  cpa_at(cpa_p1_2);
%executable cpa_sense_door(cpa_p2_1,cpa_p1_1) if  cpa_at(cpa_p2_1);
%executable cpa_sense_door(cpa_p2_1,cpa_p2_2) if  cpa_at(cpa_p2_1);
executable cpa_sense_door(cpa_p2_2,cpa_p1_2) if  cpa_at(cpa_p2_2);
executable cpa_sense_door(cpa_p2_2,cpa_p2_1) if  cpa_at(cpa_p2_2);

%% effects ------ 

cpa_move(cpa_p1_1,cpa_p1_2) causes  cpa_at(cpa_p1_2), -cpa_at(cpa_p1_1);
cpa_move(cpa_p1_1,cpa_p2_1) causes  cpa_at(cpa_p2_1), -cpa_at(cpa_p1_1);
cpa_move(cpa_p1_2,cpa_p1_1) causes  cpa_at(cpa_p1_1), -cpa_at(cpa_p1_2);
cpa_move(cpa_p1_2,cpa_p2_2) causes  cpa_at(cpa_p2_2), -cpa_at(cpa_p1_2);
cpa_move(cpa_p2_1,cpa_p1_1) causes  cpa_at(cpa_p1_1), -cpa_at(cpa_p2_1);
cpa_move(cpa_p2_1,cpa_p2_2) causes  cpa_at(cpa_p2_2), -cpa_at(cpa_p2_1);
cpa_move(cpa_p2_2,cpa_p1_2) causes  cpa_at(cpa_p1_2), -cpa_at(cpa_p2_2);
cpa_move(cpa_p2_2,cpa_p2_1) causes  cpa_at(cpa_p2_1), -cpa_at(cpa_p2_2);
cpa_sense_door(cpa_p1_1,cpa_p1_2) causes cpa_opened(cpa_p1_2);
cpa_sense_door(cpa_p1_1,cpa_p2_1) causes cpa_opened(cpa_p2_1);
%cpa_sense_door(cpa_p1_2,cpa_p1_1) causes cpa_opened(cpa_p1_1);
%cpa_sense_door(cpa_p1_2,cpa_p2_2) causes cpa_opened(cpa_p2_2);
%cpa_sense_door(cpa_p2_1,cpa_p1_1) causes cpa_opened(cpa_p1_1);
%cpa_sense_door(cpa_p2_1,cpa_p2_2) causes cpa_opened(cpa_p2_2);
cpa_sense_door(cpa_p2_2,cpa_p1_2) causes cpa_opened(cpa_p1_2);
cpa_sense_door(cpa_p2_2,cpa_p2_1) causes cpa_opened(cpa_p2_1);

%% initial state ------ 

initially cpa_at(cpa_p1_1);
initially -cpa_at(cpa_p1_2);
initially -cpa_at(cpa_p2_1);
initially -cpa_at(cpa_p2_2);
initially (cpa_opened(cpa_p1_2),-cpa_opened(cpa_p2_1))|(cpa_opened(cpa_p2_1),-cpa_opened(cpa_p1_2));

%% goal state ---------- 
goal  cpa_at(cpa_p2_2);
