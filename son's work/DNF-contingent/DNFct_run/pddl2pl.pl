
:- use_module(library(lists)).
:- dynamic executable/2.
:- dynamic cpa_executable/2.
:- dynamic causes/3.
:- dynamic cpa_causes/3.
:- dynamic cpa_initially/1.

%%%% Objects %%%%
cpa_dir(cpa_root).
cpa_dir(cpa_sub1).
cpa_dir(cpa_sub2).
cpa_dir(cpa_sub11).
cpa_dir(cpa_sub12).
cpa_dir(cpa_sub21).
cpa_dir(cpa_sub22).
cpa_dir(cpa_sub111).
cpa_dir(cpa_sub112).
cpa_dir(cpa_sub121).
cpa_dir(cpa_sub122).
cpa_dir(cpa_sub211).
cpa_dir(cpa_sub212).
cpa_dir(cpa_sub221).
cpa_dir(cpa_sub222).
cpa_dir(cpa_sub1111).
cpa_dir(cpa_sub1121).
cpa_dir(cpa_sub1211).
cpa_dir(cpa_sub1221).
cpa_dir(cpa_sub2111).
cpa_dir(cpa_sub2121).
cpa_dir(cpa_sub2211).
cpa_dir(cpa_sub2221).
cpa_dir(cpa_sub1112).
cpa_dir(cpa_sub1122).
cpa_dir(cpa_sub1212).
cpa_dir(cpa_sub1222).
cpa_dir(cpa_sub2112).
cpa_dir(cpa_sub2122).
cpa_dir(cpa_sub2212).
cpa_dir(cpa_sub2222).
cpa_dir(cpa_sub11111).
cpa_dir(cpa_sub11121).
cpa_dir(cpa_sub11211).
cpa_dir(cpa_sub11221).
cpa_dir(cpa_sub12111).
cpa_dir(cpa_sub12121).
cpa_dir(cpa_sub12211).
cpa_dir(cpa_sub12221).
cpa_dir(cpa_sub11112).
cpa_dir(cpa_sub11122).
cpa_dir(cpa_sub11212).
cpa_dir(cpa_sub11222).
cpa_dir(cpa_sub12112).
cpa_dir(cpa_sub12122).
cpa_dir(cpa_sub12212).
cpa_dir(cpa_sub12222).
cpa_dir(cpa_sub21111).
cpa_dir(cpa_sub21121).
cpa_dir(cpa_sub21211).
cpa_dir(cpa_sub21221).
cpa_dir(cpa_sub22111).
cpa_dir(cpa_sub22121).
cpa_dir(cpa_sub22211).
cpa_dir(cpa_sub22221).
cpa_dir(cpa_sub21112).
cpa_dir(cpa_sub21122).
cpa_dir(cpa_sub21212).
cpa_dir(cpa_sub21222).
cpa_dir(cpa_sub22112).
cpa_dir(cpa_sub22122).
cpa_dir(cpa_sub22212).
cpa_dir(cpa_sub22222).
cpa_file(cpa_my_file).

%%%% Constants %%%%

%%%%  Types rules %%%%

%%%% Predicates %%%%
fluent(cpa_file_in_dir(  FILE,  DIR)):-
	cpa_file( FILE), cpa_dir( DIR).

fluent(cpa_sub_dir(  PAR_DIR,  CHILD_DIR)):-
	cpa_dir( PAR_DIR), cpa_dir( CHILD_DIR).

fluent(cpa_is_cur_dir(  D)):-
	cpa_dir( D).

fluent(cpa_true).


%%%% Actions %%%%
action(cpa_cd_down(  CUR_DIR,  CHILD_DIR)):-
	cpa_dir( CUR_DIR), cpa_dir( CHILD_DIR).

action(cpa_cd_up(  CUR_DIR,  PAR_DIR)):-
	cpa_dir( CUR_DIR), cpa_dir( PAR_DIR).

action(cpa_sense_ls(  CUR_DIR,  FILE)):-
	cpa_dir( CUR_DIR), cpa_file( FILE).

action(cpa_mv(  FILE,  CUR_DIR,  TARGET_DIR)):-
	cpa_file( FILE), cpa_dir( CUR_DIR), cpa_dir( TARGET_DIR).


%%%% Preconditions %%%%
executable(cpa_cd_down(  CUR_DIR,  CHILD_DIR), [
cpa_and( cpa_and( cpa_is_cur_dir( CUR_DIR)), cpa_sub_dir( CUR_DIR,  CHILD_DIR)) ]):-
	cpa_dir( CUR_DIR), cpa_dir( CHILD_DIR).

executable(cpa_cd_up(  CUR_DIR,  PAR_DIR), [
cpa_and( cpa_and( cpa_is_cur_dir( CUR_DIR)), cpa_sub_dir( PAR_DIR,  CUR_DIR)) ]):-
	cpa_dir( CUR_DIR), cpa_dir( PAR_DIR).

executable(cpa_sense_ls(  CUR_DIR,  FILE), [
cpa_is_cur_dir( CUR_DIR) ]):-
	cpa_dir( CUR_DIR), cpa_file( FILE).

executable(cpa_mv(  FILE,  CUR_DIR,  TARGET_DIR), [
cpa_and( cpa_and( cpa_is_cur_dir( CUR_DIR)), cpa_file_in_dir( FILE,  CUR_DIR)) ]):-
	cpa_file( FILE), cpa_dir( CUR_DIR), cpa_dir( TARGET_DIR).


%%%% Effects %%%%
causes(cpa_cd_down(  CUR_DIR,  CHILD_DIR), [
cpa_and( cpa_and( cpa_is_cur_dir( CHILD_DIR)), neg(cpa_is_cur_dir( CUR_DIR))) ], 
[]):-
	cpa_dir( CUR_DIR), cpa_dir( CHILD_DIR).

causes(cpa_cd_up(  CUR_DIR,  PAR_DIR), [
cpa_and( cpa_and( cpa_is_cur_dir( PAR_DIR)), neg(cpa_is_cur_dir( CUR_DIR))) ], 
[]):-
	cpa_dir( CUR_DIR), cpa_dir( PAR_DIR).

causes(cpa_sense_ls(  CUR_DIR,  FILE), [
cpa_and( cpa_and( cpa_file_in_dir( FILE,  CUR_DIR)), cpa_true) ], 
[]):-
	cpa_dir( CUR_DIR), cpa_file( FILE).

causes(cpa_mv(  FILE,  CUR_DIR,  TARGET_DIR), [
cpa_and( cpa_and( neg(cpa_file_in_dir( FILE,  CUR_DIR))), cpa_file_in_dir( FILE,  TARGET_DIR)) ], 
[]):-
	cpa_file( FILE), cpa_dir( CUR_DIR), cpa_dir( TARGET_DIR).


%%%% Inits %%%%
cpa_initially(cpa_sub_dir(cpa_root, cpa_sub1)).
cpa_initially(cpa_sub_dir(cpa_root, cpa_sub2)).
cpa_initially(cpa_sub_dir(cpa_sub1, cpa_sub11)).
cpa_initially(cpa_sub_dir(cpa_sub1, cpa_sub12)).
cpa_initially(cpa_sub_dir(cpa_sub2, cpa_sub21)).
cpa_initially(cpa_sub_dir(cpa_sub2, cpa_sub22)).
cpa_initially(cpa_sub_dir(cpa_sub11, cpa_sub111)).
cpa_initially(cpa_sub_dir(cpa_sub11, cpa_sub112)).
cpa_initially(cpa_sub_dir(cpa_sub21, cpa_sub211)).
cpa_initially(cpa_sub_dir(cpa_sub21, cpa_sub212)).
cpa_initially(cpa_sub_dir(cpa_sub12, cpa_sub121)).
cpa_initially(cpa_sub_dir(cpa_sub12, cpa_sub122)).
cpa_initially(cpa_sub_dir(cpa_sub22, cpa_sub221)).
cpa_initially(cpa_sub_dir(cpa_sub22, cpa_sub222)).
cpa_initially(cpa_sub_dir(cpa_sub111, cpa_sub1111)).
cpa_initially(cpa_sub_dir(cpa_sub111, cpa_sub1112)).
cpa_initially(cpa_sub_dir(cpa_sub211, cpa_sub2111)).
cpa_initially(cpa_sub_dir(cpa_sub211, cpa_sub2112)).
cpa_initially(cpa_sub_dir(cpa_sub121, cpa_sub1211)).
cpa_initially(cpa_sub_dir(cpa_sub121, cpa_sub1212)).
cpa_initially(cpa_sub_dir(cpa_sub221, cpa_sub2211)).
cpa_initially(cpa_sub_dir(cpa_sub221, cpa_sub2212)).
cpa_initially(cpa_sub_dir(cpa_sub112, cpa_sub1121)).
cpa_initially(cpa_sub_dir(cpa_sub112, cpa_sub1122)).
cpa_initially(cpa_sub_dir(cpa_sub212, cpa_sub2121)).
cpa_initially(cpa_sub_dir(cpa_sub212, cpa_sub2122)).
cpa_initially(cpa_sub_dir(cpa_sub122, cpa_sub1221)).
cpa_initially(cpa_sub_dir(cpa_sub122, cpa_sub1222)).
cpa_initially(cpa_sub_dir(cpa_sub222, cpa_sub2221)).
cpa_initially(cpa_sub_dir(cpa_sub222, cpa_sub2222)).
cpa_initially(cpa_sub_dir(cpa_sub1111, cpa_sub11111)).
cpa_initially(cpa_sub_dir(cpa_sub1111, cpa_sub11112)).
cpa_initially(cpa_sub_dir(cpa_sub1211, cpa_sub12111)).
cpa_initially(cpa_sub_dir(cpa_sub1211, cpa_sub12112)).
cpa_initially(cpa_sub_dir(cpa_sub1121, cpa_sub11211)).
cpa_initially(cpa_sub_dir(cpa_sub1121, cpa_sub11212)).
cpa_initially(cpa_sub_dir(cpa_sub1221, cpa_sub12211)).
cpa_initially(cpa_sub_dir(cpa_sub1221, cpa_sub12212)).
cpa_initially(cpa_sub_dir(cpa_sub1112, cpa_sub11121)).
cpa_initially(cpa_sub_dir(cpa_sub1112, cpa_sub11122)).
cpa_initially(cpa_sub_dir(cpa_sub1212, cpa_sub12121)).
cpa_initially(cpa_sub_dir(cpa_sub1212, cpa_sub12122)).
cpa_initially(cpa_sub_dir(cpa_sub1122, cpa_sub11221)).
cpa_initially(cpa_sub_dir(cpa_sub1122, cpa_sub11222)).
cpa_initially(cpa_sub_dir(cpa_sub1222, cpa_sub12221)).
cpa_initially(cpa_sub_dir(cpa_sub1222, cpa_sub12222)).
cpa_initially(cpa_sub_dir(cpa_sub2111, cpa_sub21111)).
cpa_initially(cpa_sub_dir(cpa_sub2111, cpa_sub21112)).
cpa_initially(cpa_sub_dir(cpa_sub2211, cpa_sub22111)).
cpa_initially(cpa_sub_dir(cpa_sub2211, cpa_sub22112)).
cpa_initially(cpa_sub_dir(cpa_sub2121, cpa_sub21211)).
cpa_initially(cpa_sub_dir(cpa_sub2121, cpa_sub21212)).
cpa_initially(cpa_sub_dir(cpa_sub2221, cpa_sub22211)).
cpa_initially(cpa_sub_dir(cpa_sub2221, cpa_sub22212)).
cpa_initially(cpa_sub_dir(cpa_sub2112, cpa_sub21121)).
cpa_initially(cpa_sub_dir(cpa_sub2112, cpa_sub21122)).
cpa_initially(cpa_sub_dir(cpa_sub2212, cpa_sub22121)).
cpa_initially(cpa_sub_dir(cpa_sub2212, cpa_sub22122)).
cpa_initially(cpa_sub_dir(cpa_sub2122, cpa_sub21221)).
cpa_initially(cpa_sub_dir(cpa_sub2122, cpa_sub21222)).
cpa_initially(cpa_sub_dir(cpa_sub2222, cpa_sub22221)).
cpa_initially(cpa_sub_dir(cpa_sub2222, cpa_sub22222)).
cpa_initially(cpa_is_cur_dir(cpa_root)).
cpa_initially(cpa_oneof([cpa_file_in_dir(cpa_my_file, cpa_sub11), cpa_file_in_dir(cpa_my_file, cpa_sub21), cpa_file_in_dir(cpa_my_file, cpa_sub12), cpa_file_in_dir(cpa_my_file, cpa_sub22), cpa_file_in_dir(cpa_my_file, cpa_sub111), cpa_file_in_dir(cpa_my_file, cpa_sub211), cpa_file_in_dir(cpa_my_file, cpa_sub121), cpa_file_in_dir(cpa_my_file, cpa_sub221), cpa_file_in_dir(cpa_my_file, cpa_sub112), cpa_file_in_dir(cpa_my_file, cpa_sub212), cpa_file_in_dir(cpa_my_file, cpa_sub122), cpa_file_in_dir(cpa_my_file, cpa_sub222), cpa_file_in_dir(cpa_my_file, cpa_sub1111), cpa_file_in_dir(cpa_my_file, cpa_sub2111), cpa_file_in_dir(cpa_my_file, cpa_sub1211), cpa_file_in_dir(cpa_my_file, cpa_sub2211), cpa_file_in_dir(cpa_my_file, cpa_sub1121), cpa_file_in_dir(cpa_my_file, cpa_sub2121), cpa_file_in_dir(cpa_my_file, cpa_sub1221), cpa_file_in_dir(cpa_my_file, cpa_sub2221), cpa_file_in_dir(cpa_my_file, cpa_sub1112), cpa_file_in_dir(cpa_my_file, cpa_sub2112), cpa_file_in_dir(cpa_my_file, cpa_sub1212), cpa_file_in_dir(cpa_my_file, cpa_sub2212), cpa_file_in_dir(cpa_my_file, cpa_sub1122), cpa_file_in_dir(cpa_my_file, cpa_sub2122), cpa_file_in_dir(cpa_my_file, cpa_sub1222), cpa_file_in_dir(cpa_my_file, cpa_sub2222), cpa_file_in_dir(cpa_my_file, cpa_sub11111), cpa_file_in_dir(cpa_my_file, cpa_sub12111), cpa_file_in_dir(cpa_my_file, cpa_sub11211), cpa_file_in_dir(cpa_my_file, cpa_sub12211), cpa_file_in_dir(cpa_my_file, cpa_sub11121), cpa_file_in_dir(cpa_my_file, cpa_sub12121), cpa_file_in_dir(cpa_my_file, cpa_sub11221), cpa_file_in_dir(cpa_my_file, cpa_sub12221), cpa_file_in_dir(cpa_my_file, cpa_sub11112), cpa_file_in_dir(cpa_my_file, cpa_sub12112), cpa_file_in_dir(cpa_my_file, cpa_sub11212), cpa_file_in_dir(cpa_my_file, cpa_sub12212), cpa_file_in_dir(cpa_my_file, cpa_sub11122), cpa_file_in_dir(cpa_my_file, cpa_sub12122), cpa_file_in_dir(cpa_my_file, cpa_sub11222), cpa_file_in_dir(cpa_my_file, cpa_sub12222), cpa_file_in_dir(cpa_my_file, cpa_sub21111), cpa_file_in_dir(cpa_my_file, cpa_sub22111), cpa_file_in_dir(cpa_my_file, cpa_sub21211), cpa_file_in_dir(cpa_my_file, cpa_sub22211), cpa_file_in_dir(cpa_my_file, cpa_sub21121), cpa_file_in_dir(cpa_my_file, cpa_sub22121), cpa_file_in_dir(cpa_my_file, cpa_sub21221), cpa_file_in_dir(cpa_my_file, cpa_sub22221), cpa_file_in_dir(cpa_my_file, cpa_sub21112), cpa_file_in_dir(cpa_my_file, cpa_sub22112), cpa_file_in_dir(cpa_my_file, cpa_sub21212), cpa_file_in_dir(cpa_my_file, cpa_sub22212), cpa_file_in_dir(cpa_my_file, cpa_sub21122), cpa_file_in_dir(cpa_my_file, cpa_sub22122), cpa_file_in_dir(cpa_my_file, cpa_sub21222), cpa_file_in_dir(cpa_my_file, cpa_sub22222)])).
cpa_initially(neg(X)) :- fluent(X), \+ cpa_initially(X), \+ unknown(X).
unknown(X):- fluent(X),
            findall(L, (cpa_initially(cpa_oneof(Y)), member(L,Y)), LUnk),
            member(X, LUnk).
unknown(X):- fluent(X), cpa_unknown(X).
unknown(X) :- fluent(X), (cpa_initially(cpa_or(Y)),in_or(Y,X);
          cpa_initially(cpa_or(Y,Z)), (in_or(Y,X);in_or(Z,X))), !.
unknown(X) :- fluent(X), cpa_initially(cpa_oneof(ListBig)), member(ListSmall,ListBig),
           member(X,ListSmall).
in_or(X,X) :- !.
in_or(neg(X),X) :- !.
in_or(cpa_or(Y),X) :- in_or(Y,X).
in_or(cpa_or(Y,Z),X) :- (in_or(Y,X);in_or(Z,X)).
cpa_unknown(nop).

%%%% Goals %%%%
plan_goal(cpa_file_in_dir(cpa_my_file, cpa_root)).
