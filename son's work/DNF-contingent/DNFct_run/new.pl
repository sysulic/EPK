%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% This version includes neg tracking
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


:- use_module(library(lists)).
:- use_module(library(ordsets)).

:- dynamic applicable/2.
:- dynamic in_goals/1.
:- dynamic dep_goals/1.
:- dynamic always_true/1.
:- dynamic always_false/1.
:- dynamic screen_print/0.
:- dynamic cpa_debug/0.
:- dynamic option/1.
:- dynamic cpa_stats/0.
:- dynamic dumpo_stats/3.
:- dynamic duals/2.


%option([noforward,noanalyze,no_goal_split,no_oneof]).   
option([ no_duals, no_goal_split, no_oneof  ]).      %%do all simplifications
   %%noforward : no forward simplification
   %%noanalyze : remove backward analysis
   %%no_goal_split: do not split theories for independent goals
   %%no_oneof : do not combine oneof in the initial state
   %%no_duals : remove the duals computation



cpa_debug.        %%uncomment to print debug messages
cpa_stats.
% screen_print.     %%uncomment if you want theories printed on the screen
                   %%each theory is separated by a sequence of '$'

remove_duplicates(L,L1) :- remove_dups(L,L1).

main :-
        convert_executable,
        convert_causes,
	extract_deps,
        extract_applicable,

	(cpa_stats -> findall(Ax, action(Ax), LAx), findall(Fx, fluent(Fx), LFx),
	              length(LAx,OrigA), length(LFx,OrigF), statistics(walltime,_); true),

	option(Opt),

	(member(noforward,Opt) -> 
	    findall(F,fluent(F),FluentsComputed),
	    findall(neg(F),fluent(F),NegFluentsComputed),
	    findall(Acc,action(Acc),Appliedx);
	    time_closure(0,[],[],[],[],FluentsComputed, NegFluentsComputed, Appliedx,_,T)
	),


	quick_bad_actions(Appliedx, Applied),

	findall(Flu,(member(Act,Applied),
	             cpa_executable(Act,Conds),
		     member(Flu,Conds),
		     fluent(Flu)), Additional),
	findall(ArbitraryFluent,(member(ArbitraryFluent,Additional), 
                                 \+member(ArbitraryFluent,FluentsComputed)), 
                                Differences),
	length(Differences,LengthDiffs), 
	(cpa_debug -> format("There are ~q new fluents~n",[LengthDiffs]); true),
	append(FluentsComputed,Additional,Additional1),
	remove_duplicates(Additional1,Additional2),

	(cpa_stats -> length(Applied,ForA), findall(F1,member(neg(F1),NegFluentsComputed), XX),
	              append(XX,Additional2,XXX), remove_duplicates(XXX,XXXX), length(XXXX,ForF),
		      statistics(walltime,[_,Tfor]); true),
	
	(member(noanalyze,Opt) ->
	    Cleaned1 = Applied;
	    analyze_theory(FluentsComputed, NegFluentsComputed,Applied,Cleaned1)
	),



        findall(L, (member(neg(L), NegFluentsComputed), 
	            \+(member(L, FluentsComputed))), FlToAdd),
        append(FluentsComputed, FlToAdd, FlToDump),

	(cpa_stats -> length(Cleaned1,BackA), BackF=ForF, statistics(walltime,[_,Tback]); true),

	goal_indep(Cleaned1),
	
	(cpa_stats -> count_goals(FinalGoals), findall(Gx,plan_goal(Gx),LGx), length(LGx,InitialGoals),
	    statistics(walltime,[_,Tgoal]); true),
	
	(\+member(no_duals,Opt) ->    determine_duals(Cleaned1),
	                              retractall(duals(_,_)); true),

	(cpa_stats -> format("Forward Simplfication: ~n",[]),
	              format("    Original # of Actions and Fluents: ~q/~q~n",[OrigA,OrigF]),
		      format("    Reduced  # of Actions and Fluents: ~q/~q~n",[ForA,ForF]),
		      format("    Execution Time: ~qms.~n",[Tfor]),
		      format("Backward Simplification: ~n",[]),
		      format("    Original # of Actions and Fluents: ~q/~q~n",[ForA,ForF]),
		      format("    Reduced  # of Actions and Fluents: ~q/~q~n",[BackA,BackF]),
		      format("    Execution Time: ~qms.~n",[Tback]),
		      format("Independent Goals Detection:~n",[]),
		      format("    Original Number of Goals: ~q~n",[InitialGoals]),
		      format("    Number of Goals/Theories: ~q~n",[FinalGoals]),
		      format("    Execution Time: ~qms.~n",[Tgoal]); true),


		      
	create_theories(T,Cleaned1, FlToDump),

	option(Opt1),
	(cpa_stats,\+member(no_oneof,Opt1) -> dumpo_stats(Cox1,Cox2,Coxt),
		      format("Combination of Initial States:~n",[]),
		      format("    Original Number of States: ~q~n",[Cox1]),
		      format("    Final Number of States:    ~q~n",[Cox2]),
		      format("    Execution Time: ~qms.~n",[Coxt]); true).


flip_literal(neg(X),X) :- !.
flip_literal(X,neg(X)).

%quick_bad_actions(L,L).
quick_bad_actions([],[]).
quick_bad_actions([A|B],[A|C]) :-
	findall(X,(cpa_causes(A,E,_), member(X,E),flip_literal(X,Y),\+member(Y,E)),[_|_]),!,
	quick_bad_actions(B,C).
quick_bad_actions([_A|B],C) :-
	quick_bad_actions(B,C).

count_goals(N) :-
	findall(In,in_goals(In),LInx),
	findall(De,dep_goals(De),LDe),
	(LDe=[] -> length(LInx,N); length(LInx,N1), N is N1+1).

write_fluents([]).
write_fluents([X|Y]):- format("~q~n",[X]), write_fluents(Y).

write_actions([]).
write_actions([X|Y]):- format("~q~n",[X]), write_actions(Y).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% Duals
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

determine_duals(Actions) :- 
	collect_duals(Actions,D),
	check_init_duals(D,D1),
	remove_repeated(D1,D2),
	assert_duals(D2).

remove_repeated(In,Out) :-
	findall(X, twice(X,In), List),
	remove_all_containing(In,List,Out).
twice(X,In) :-
	findall(Y, (member((X,Y),In);member((Y,X),In)), List),
	remove_duplicates(List,List1),
	List1=[_,_|_].
remove_all_containing([],_,[]).
remove_all_containing([(A,B)|Y],X,Z) :- 
	(A=X; B=X), !, remove_all_containing(Y,X,Z).
remove_all_containing([(A,B)|Y], X, [(A,B)|Z]) :- remove_all_containing(Y,X,Z).

collect_duals(Actions, D) :-
	always_true(TT), always_false(FF),
	findall((X,Y), (cpa_causes(_A,EFF,_),
	                member(X,EFF),
			member(neg(Y),EFF),
			\+ (X = neg(_)),
			\+ (X=Y),
			\+member(X,TT),
			\+member(Y,TT),
			\+member(X,FF),
			\+member(Y,FF)), D1),
	remove_duplicates(D1,D2),
	remove_opposites(D2,D3),
	check_always_duals(D3,D,Actions).

remove_opposites([],[]).
remove_opposites([(A,B)|Rest], Rest1) :-
	member((B,A), Rest),!,
	remove_opposites(Rest,Rest1).
remove_opposites([K|Rest],[K|Rest1]) :-
	remove_opposites(Rest,Rest1).

check_always_duals([],[],_).
check_always_duals([(A,B)|Rest], [(A,B) | Rest1], Actions) :-
	findall(Act, (action(A),     %member(Act,Actions), 
	              cpa_causes(Act,Eff,_),
		      (member(A,Eff),\+member(neg(B),Eff);
                       member(neg(A),Eff),\+member(B,Eff);
		       member(B,Eff),\+member(neg(A),Eff);
		       member(neg(B),Eff),\+member(A,Eff))), []),!,
	check_always_duals(Rest,Rest1,Actions).
check_always_duals([_|Rest], Rest1,Actions) :-
	check_always_duals(Rest,Rest1,Actions).

check_init_duals([], []).
check_init_duals([(A,B)|Rest], [(A,B)|Rest1]) :-
	(check_simple_init(A,B) ;
	 check_implicit_init(A,B)),!,
	check_init_duals(Rest,Rest1).
check_init_duals([_|Rest], Rest1) :-
	check_init_dualsRest(Rest,Rest1).
	
check_simple_init(A,B) :-
	cpa_initially(A), 
	cpa_initially(neg(B)),!.
check_simple_init(A,B) :-
	cpa_initially(B), 
	cpa_initially(neg(A)),!.

check_implicit_init(A,B) :-
	write('YOU SHOULD NOT REACH THIS POINT IN THE CODE!!!!!!'), nl,
	cpa_initially(cpa_oneof(L)),
	length(L,2),
	member(A,L), member(B,L).


assert_duals([]).
assert_duals([(A,B)|Rest]) :-
	format("FOUND DUALS: ~q and ~q ~n ",[A,B]),
	duals(A,B),
	assert_duals(Rest).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% GOALS ORDERING
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

goal_indep(Actions) :-
	retractall(in_goals(_)),
	retractall(dep_goals(_)),
	findall(G,plan_goal(G),Gs),
	normalize_and_dump(Gs,Actions).

normalize_and_dump([],_).
normalize_and_dump([G|Gs],Actions) :-
	findall(C,cv_and(G,C), Cs),
	dump_out(Cs,Actions),
	normalize_and_dump(Gs,Actions).

dump_out(Form,Actions) :-
	collect_all_goals(Form,Goals),
	(is_indep(Goals,Actions) -> assert(in_goals(Form)); 
	    assert(dep_goals(Form))).

collect_all_goals([],[]) :- !.
collect_all_goals([A|B], Res) :- !,
	collect_all_goals(A,L1),
	collect_all_goals(B,L2),
	append(L1,L2,Res).
collect_all_goals(A,[A]).

is_indep(Goals, Actions) :-
	findall(F,(member(F,Goals), check_indep(F,Actions)),List),
	length(Goals,N),
	length(List,N).

check_indep(Goal,Actions) :-
	flip_fluent(Goal,NGoal),
	findall(Ac, (member(Ac,Actions),
	             cpa_causes(Ac,Effs,_),
		     member(NGoal,Effs)),  []).
	
flip_fluent(neg(X),X) :- !.
flip_fluent(X,neg(X)).



	

%%%%%%%%%%%%%%%%%%%
%% Analyze Theory

analyze_theory(Fluents,NegFluents, Rules, Cleaned) :-
	count_fluents(Fluents,NegFluents),
	always_true(AT), always_false(AF),
	clean_theory(Rules,AT,AF,Cleaned),
	length(Rules,R1), length(Cleaned,R2),
	(cpa_debug -> format("Reduced from ~q to ~q actions~n",[R1,R2]); true).
%	check_for_wrong_consequence(Cleaned,AT,AF).

%remove_duplicates(L,L1) :- remove_dups(L,L1).	
	
%%
clean_theory([],_,_,[]).
clean_theory([A|B],AT,AF,B1) :-
	invalidated(A,AT,AF),
	 !,
	 clean_theory(B,AT,AF,B1).
clean_theory([A|B],AT,AF,[A|B1]) :-
	clean_theory(B,AT,AF,B1).

invalidated(A,AT,_AF) :-
	cpa_executable(A,List),
	member(neg(F),List),
	member(F,AT).	 
%	format("Removing action ~q because of neg(~q)~n",[A,F]).
invalidated(A,_AT,AF) :-
	cpa_executable(A,List),
	member(F,List),
	member(neg(F),AF).
%	format("Removing action ~q because of ~q~n",[A,F]).

%%
check_for_wrong_consequence([],_,_).
check_for_wrong_consequence([A|B],AT,AF) :-
	cpa_causes(A,Cons,_),
	(non_disjoint(Cons,AT,F)->format("    remove ~q due to bad positive causes ~q~n",[A,F]); true),
	(non_disjoint(Cons,AF,G)->format("    remove ~q due to bad negative causes ~q~n",[A,G]); true),
	 check_for_wrong_consequence(B,AT,AF).

non_disjoint(L1,ATF,F) :-
	member(F,L1),
	contrary(F,F1),
	member(F1,ATF).
	
%%
count_fluents(True,False) :-
	length(True,NT), length(False,NF),
	(cpa_debug->format("There are ~q true and ~q false ~n",[NT,NF]); true),
	findall(X1,(member(X1,True),cpa_initially(X1),\+member(neg(X1),False)), AlwaysTrue1),
	remove_duplicates(AlwaysTrue1,AlwaysTrue),
	length(AlwaysTrue,NAL),
	(cpa_debug->format("There are ~q fluents that are always true.~n",[NAL]); true),
	assert(always_true(AlwaysTrue)),
	findall(X2,(member(neg(X2),False),cpa_initially(neg(X2)),\+member(X2,True)), AlwaysFalse1),
	length(AlwaysTrue,NAL), length(AlwaysFalse1,NAF),
	assert(always_false(AlwaysFalse1)),
	(cpa_debug->format("There are ~q fluents that are always false.~n",[NAF]);true).

initially(F) :- cpa_initially(F).
initially(F1) :- fluent(F), \+cpa_initially(F), \+cpa_initially(neg(F)),
	contrary(F,F1).

contrary(neg(F),F).
contrary(F,neg(F)):- \+(F=neg(_)).


%%
goal_reachable(Goals, Fluents,Stream) :-
	sgoal_reachable(Goals,Fluents,Reachable),
	dump_reach([goal1,goal2,goal3,goal4,goal5,goal6,goal7,goal8,goal9,goal10,goal11,goal12,goal13,goal14],Reachable,Stream).

dump_reach([],_,_S).
dump_reach([A|B],Reachable,Stream) :-
	findall(C,clause(A,C),List),
	sub_dump_reach(List,Reachable,Stream,A),
	dump_reach(B,Reachable,Stream).
sub_dump_reach([],_,_,_).
sub_dump_reach([holds(F,_L)|Rest],Reachable,Stream,Goal) :-
	(acceptable_dump_reach(F,Reachable) ->
	    format(Stream,"~q :- holds(~q,length).~n",[Goal,F]);
	    true),
	    sub_dump_reach(Rest,Reachable,Stream,Goal).

acceptable_dump_reach(neg(_),_) :- !.
acceptable_dump_reach(F,Reachable) :-
	member(F,Reachable).

sgoal_reachable([],_Fluents,[]).
sgoal_reachable([neg(A)|Rest], Fluents,[neg(A)|B]) :-
	!,
	sgoal_reachable(Rest, Fluents,B).
sgoal_reachable([A|B], Fluents, List) :-
	sgoal_reachable(B,Fluents,Rea),
	(member(A,Fluents) -> List = [A|Rea]; List=Rea).

%%
bad_actions(0,Rules,Stream) :-
	time_actions(0,Actions),
	dump_missing(0,Rules,Actions,Stream).
bad_actions(Time,Rules,Stream) :-
	Time > 0,
	Time1 is Time-1,
	time_actions(Time,Applied),
	dump_missing(Time,Rules,Applied,Stream),
	bad_actions(Time1,Rules,Stream).

dump_missing(_Time,[],_Applied,_Stream).
dump_missing(Time,[A|B], Applied,Stream) :-
	(member(A,Applied) -> true;
	    format(Stream,":- occ(~q,~q).~n",[A,Time])),
	    dump_missing(Time,B,Applied,Stream).

%%


%%
%% Necessary for Sicstus 4
%%

simplify_neg([],[]).
simplify_neg([neg(_)|Rest],Rest1):- !,
        simplify_neg(Rest,Rest1).
simplify_neg([A|Rest],[A|Rest1]):- !,
        simplify_neg(Rest,Rest1).

extract_deps :-
	clause(cpa_executable(A,B),C),
        simplify_neg(B,B1),
	make_clauses(B1,A,C),fail.
extract_deps.

make_clauses([],A,C) :-
	!, assert((dep(true,A) :- C)).
make_clauses(List,A,C) :-
	sub_make_clauses(List,A,C).
sub_make_clauses([],_,_).
sub_make_clauses([neg(_)|Y],A,C) :- !,
	sub_make_clauses(Y,A,C).
sub_make_clauses([X|Y],A,C) :-
	assert((dep(X,A) :- C)),
	sub_make_clauses(Y,A,C).

extract_applicable :-
	clause(cpa_executable(A,B),C),
	make_clause_a(A,C,B,_Fluents,true), fail.
extract_applicable.

make_clause_a(A,C,[],Fluents,R) :-
	assert((applicable(A,Fluents) :- R,C)).
make_clause_a(A,B,[neg(_)|Y],Fluents,Rest) :- !,
	make_clause_a(A,B,Y,Fluents,Rest).
make_clause_a(A,B,[X|Y],Fluents,Rest) :-
	make_clause_a(A,B,Y,Fluents,((member(X,Fluents);unknown(X)),Rest)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% TIME CLOSURE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

literal(neg(F)) :- fluent(F),!.
literal(F) :- fluent(F).

time_closure(0,_OldPos,_OldNeg,_OldActions,_OldNew,FinalPos,FinalNeg, FinalApp,FinalNew,T) :-
	findall(G, (cpa_initially(G),fluent(G)), F),
	findall(neg(MG), (cpa_initially(neg(MG)),fluent(MG)), MMM),
	findall(U1, (fluent(U1), unknown(U1)), Upos),
	findall(neg(U2), (fluent(U2),unknown(U2)), Uneg),
	append(F,Upos, FU),
	append(MMM, Uneg, NU),
	findall(A, (dep(true,A)), Applied),
	assert(time_actions(0,Applied)),
	length(Applied,NAP),
	(cpa_debug->format("    Time 0: ~q actions~n",[NAP]);true),
	list_to_ord_set(Applied,Applied1),
	length(FU,N),length(Applied,NA),
	assert(level(0,FU,Applied1)),
	(cpa_debug->format("Time 0: ~q actions and ~q fluents~n",[NA,N]);true),!,
	time_closure(1,FU,NU,Applied1,FU,FinalPos,FinalNeg,FinalApp,FinalNew,T).

time_closure(InT,F1,OldNegFluents,Applied1,Mod,FinalPos,FinalNeg,FinalApp,FinalNew, OutT) :-
	InT > 0,
	T1 is InT+1,
	step_closure(Mod,F1,OldNegFluents, F, NewNegFluents, Applied1, Applied,NewOnes,T,NegCons),
	length(Applied,NAP),
	(cpa_debug->format("    Time ~q: ~q actions~n",[T,NAP]);true),
	assert(time_actions(T,Applied)),
	length(F,NF), length(Applied,NA),
	append(NewOnes,NegCons,LevelCons1),
	remove_duplicates(LevelCons1,LevelCons),
	assert(level(T,LevelCons,Applied)),
	(cpa_debug->format("Time ~q: ~q actions and ~q fluents ~n",[T,NA,NF]);true),!,
	(Mod = [] -> FinalPos=F, FinalNeg=NewNegFluents,FinalApp=Applied,FinalNew=NewOnes,OutT=T1;
	    time_closure(T1,F,NewNegFluents,Applied,NewOnes,FinalPos,FinalNeg,FinalApp,FinalNew,OutT)).

step_closure(Source,OldFluents,OldNegFluents, NewFluents, NewNegFluents, AppliedOld, AppliedNew,NewOnes,_Time,NegCons) :-
	collect_applicable(Source,OldFluents,AppliedOld,Tentative),
	/* format("collected actions~n",[]),*/ 
	append(Tentative, AppliedOld,AppliedNew11),
	list_to_ord_set(AppliedNew11,AppliedNew),
	collect_consequences(AppliedNew,OldFluents,OldNegFluents,Cons,NegCons),
	remove_duplicates(Cons,NewOnes),
	append(NegCons,OldNegFluents,NewNegFluents1),
	remove_duplicates(NewNegFluents1,NewNegFluents),
	append(NewOnes,OldFluents, NewFluents1),
	remove_duplicates(NewFluents1,NewFluents).


collect_applicable(Source,OldFluents,AppliedOld,AppliedNew) :-
 	find_relevant(Source,List),
 	findall(A,(member(A,List),applicable(A,OldFluents),\+member(A,AppliedOld)), AppliedNew1),
 	remove_duplicates(AppliedNew1,AppliedNew).


find_relevant([],[]).
find_relevant([F|Rest],List) :-
	make_template(F,Temp),
	findall(Act,clause(dep(Temp,Act),_Body),L1),
	find_relevant(Rest,L2),
	append(L1,L2,List1),
	remove_variants(List1,List).
make_template(F,T) :-
	functor(F,Name,Args),
	functor(T,Name,Args).

remove_variants([],[]).
remove_variants([X|Rest],Y) :-
	variantpresent(X,Rest),!,
	remove_variants(Rest,Y).
remove_variants([X|Rest],[X|Y]) :-
	remove_variants(Rest,Y).

variantpresent(X,[Y|_Z]) :-
	functor(X,F,N),
	functor(Y,F,N),!.
variantpresent(X,[_Y|Z]) :-
	variantpresent(X,Z).

dumbo.

find_instance(F,A,A1) :-
	findall(X,(X=A,dep(F,X)),List),
	member(A1,List).

my_sublist([],_).
my_sublist([neg(_)|B],F) :- !,
	my_sublist(B,F).
my_sublist([A|B],F) :-
	member(A,F), my_sublist(B,F).
%%

collect_consequences([],_,_,[],[]).
collect_consequences([Action|Rest],OldFluents,OldNegFluents, List, NewNegs) :-
	findall(Res,(cpa_causes(Action,Res1,_),member(Res,Res1),\+(Res=neg(_)),\+member(Res,OldFluents)),List1),
	findall(Res,(cpa_causes(Action,Res1,_),member(Res,Res1),Res=neg(_),\+member(Res,OldNegFluents)),NList1),
	list_to_ord_set(List1,List2),
	collect_consequences(Rest,OldFluents,OldNegFluents, R1, R2),
	append(List2 ,R1,List),
	append(NList1,R2,NewNegs).

negate(neg(F),F) :- !.
negate(F, neg(F)).

valid([],_).
valid([neg(_A)|B],Base) :-
	!, 
	valid(B,Base).
valid([A|B],Base) :-
	member(A,Base),
	valid(B,Base).
%	(member(A,Base) ; negate(A,A1),\+member(A1,Base)),
%	valid(B,Base).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

generate_name :-
	retractall(name_index(_)),
	assert(name_index(0)).
get_file_name(NAME) :-
	name_index(N),
	name('theory_',L1),
	name(N,L2),
	name('.al',L3),
	append(L1,L2,X1),
	append(X1,L3,X2),
	name(NAME,X2),
	N1 is N+1,
	retractall(name_index(_)),
	assert(name_index(N1)).
first_file :-
	name_index(1).

create_theories(Time, Rules, Fluents) :-
	option(Opt),
	generate_name,
	    tell('theory_names'),
	    dump_file_names,
	    told,
	(\+member(no_goal_split,Opt) ->
	    create_independent_theories(Time,Rules,Fluents),!,
	    create_dependent_theories(Time,Rules,Fluents);
	    findall(A,plan_goal(A),List),
	    write_theory(Fluents,Rules,[List],indep)).

create_independent_theories(_Time,Rules,Fluents) :-
	in_goals(G),
	back_closure(0 ,Rules,Fluents,NewRules,NewFluents,G, Rules,Fluents),
%	remove_useless_oneof(NewFluents),
	format("WRITING INDEP GOAL THEORY ~q~n",[G]),
	write_theory(Fluents, NewRules,G,indep),
	fail.
create_independent_theories(_,_,_).

create_dependent_theories(_Time, Rules, Fluents) :-
	findall(A, dep_goals(A), Goals),
	(Goals = [] -> true; 
	    back_closure(0,Rules,Fluents,NewRules,NewFluents, Goals,Rules,Fluents),
%	    remove_useless_oneof(NewFluents),
	    write_theory(Fluents,NewRules, Goals, dep)
	).
		

remove_useless_oneof(Fl) :-
	findall(cpa_oneof(L), cpa_initially(cpa_oneof(L)), ALL),
	complete_literal_list(Fl,Fl1),
	remove_them(ALL,Fl1).

complete_literal_list([],[]).
complete_literal_list([A|B],[A,C|Rest]) :-
	flip_literal(A,C),
	complete_literal_list(B,Rest).

remove_them([],_).
remove_them([cpa_oneof(La)|Rest],Fl) :-
	make_oneof_list(La,L),
	(intersect_list(L,Fl) -> true; retract(cpa_initially(cpa_oneof(La)))),
	remove_them(Rest,Fl).

make_oneof_list([],[]).
make_oneof_list([A|B],Result) :-
	make_oneof_list(B,R1),
	(A=[_|_] -> append(A,R1,R2); R2=[A|R1]),
	remove_duplicates(R2,Result).

intersect_list(L1,L2) :-
	member(X,L1), member(X,L2),!.

%%%%%%%%%%%%%%%%%%%%%%%


get_all_fluents([],[]):-!.
get_all_fluents([A|B], C) :-!,
	get_all_fluents(B,B1),
	get_all_fluents(A,A1),
	append(A1,B1,C).
get_all_fluents(F,[F]).

back_closure(0,_Applied,_Fluents,NewRules,NewFluents, Seed,ORIGINAL, ORFLU) :-
	get_all_fluents(Seed, StartSeed),
	remove_duplicates(StartSeed,StartSeed1),!,
        T1 is 1,
        back_closure(T1, [], StartSeed1, NewRules, NewFluents, Seed, ORIGINAL,ORFLU).
back_closure(T,NewApp,NewFlu,NewNewApplied,NewNewFluents, Seed, ORIGINAL,ORFLU) :-
  findall(A,(member(A,ORIGINAL),\+member(A,NewApp),cpa_causes(A,Fl1,_),
	     member(Fl,Fl1), member(Fl,NewFlu)),
	  ListActions),
  append(NewApp,ListActions,NewApplied1),
  remove_duplicates(NewApplied1,NewApplied),
  manual_collect(ListActions,ORFLU,CondsA),
  findall(X,(member(X,CondsA),(member(X,ORFLU);flip_literal(X,Y),member(Y,ORFLU))),CondsB),
  append(CondsB,NewFlu,NewFluents1),
  remove_duplicates(NewFluents1,NewFluents),
  length(NewApplied,NAP),
  (cpa_debug->format("Time ~q has ~q actions~n",[T,NAP]);true), 
  (NewApplied = NewApp, NewFluents=NewFlu -> NewNewApplied=NewApplied,NewNewFluents=NewFluents;
   T1 is T+1,
   back_closure(T1, NewApplied, NewFluents,NewNewApplied,NewNewFluents,Seed, ORIGINAL,ORFLU)), !.

	
manual_collect([],_F,[]).
manual_collect([A|As],Fluents,NewF) :-
	cpa_executable(A,X1),
	cpa_causes(A,_,X2),
	append(X1,X2,New1),
%	findall(Y,(member(Y,X3),member(Y,Fluents)), New1),
	manual_collect(As,Fluents,New2),
	append(New1,New2,NewF).

%remove_duplicates(L,L1) :- remove_dups(L,L1).

%%%%%%%%%%%%%%%%%%%%%%%

write_theory(Fluents,Rules, Goal,Mode) :-
	create_theory(Fluents, Rules, Goal,Mode), !.

create_theory(FluentsComputed, Applied, Goal,Mode) :-
	get_file_name(NAME),
	(cpa_debug->format("starting ~q~n",[NAME]);true),

        (always_true(AT)->true; AT=[]),
        (always_false(AF)->true; AF=[]),
	findall(Flu,(member(Act,Applied),
	             cpa_executable(Act,Conds),
		     member(Flu,Conds),
		     fluent(Flu)), Additional),

	append(FluentsComputed,Additional,Additional1),
	remove_duplicates(Additional1,Additional2),
        get_real_actions(Applied, AT, AF, NewApplied), 
	(screen_print -> format("$$$$$$$$$$~n",[]); tell(NAME)),

	(first_file -> dump_fluents(Additional2,[]); true),
	nl,format("%% actions ------ ~n~n",[]),
	dump_actions(NewApplied),
	nl,format("%% executable ------ ~n~n",[]),
        dump_executable(NewApplied),
	nl,format("%% effects ------ ~n~n",[]),
        dump_action_effects(NewApplied, Additional2),
	nl,format("%% initial state ------ ~n~n",[]),
        (first_file ->  dump_initial(FluentsComputed,NewApplied); true),
	nl,format("%% goal state ---------- ~n",[]),
        (Mode=indep -> dump_single_goal(Goal);
	    dump_goal_list(Goal)),
	(screen_print -> true;  told),
	(cpa_debug-> write('completed theory'),nl; true).

dump_file_names :-
	findall(X, in_goals(X),L1),
	length(L1,N1),
	findall(X, dep_goals(X),L2),
	length(L2,N2),
	(N2 > 0 ->	N is N1+1;
	    N is N1),
	dump_file_names(0,N).
dump_file_names(N,N) :- !, format("~n",[]).
dump_file_names(M,N):- M < N,
	name('theory_',L1),
	name('.al',L3),
	name(M,L2),
	append(L1,L2,X1),
	append(X1,L3,X2),
	name(NAME,X2),
	write(NAME),write(' '),
	M1 is M+1,
	dump_file_names(M1,N).

get_real_actions([],_,_,[]).
get_real_actions([R|Rest],AT,AF,NewRest):- 
        findall(Conds, (cpa_executable(R,Conds), (member(X,AT), member(neg(X),Conds);member(X,AF),member(X,Conds))), [_|_]),!,
	(cpa_debug->format("Discarding from real action ~q~n",[R]);true),
        get_real_actions(Rest,AT,AF,NewRest). 

get_real_actions([R|Rest],AT,AF,[R|NewRest]):- 
        get_real_actions(Rest,AT,AF,NewRest). 


dump_single_goal(G) :-
	dump_one_goal(G).

%dump_goal(G) :-
%	findall(X,in_goals(X), Indeps),
%	dump_goal_list(Indeps,indep),
%	findall(Y,dep_goals(Y), Deps),
%	dump_goal_list(Deps, dep).

dump_goal_list([]).
dump_goal_list([A|B]) :-
	dump_one_goal(A),
	dump_goal_list(B).
dump_one_goal(Goal) :-
	format("goal ",[]),
	length(Goal,N),
	(N > 1 -> dump_goal_or(Goal);
	    dump_goal_and(Goal)),
	format(";~n",[]).
	
dump_goal_or([]).
dump_goal_or([A|Rest]):-
        format("(",[]),
        dump_goal_and([A]),
        format(")",[]),
        (Rest == []  -> 
           true;
           format("|",[])
        ),
        dump_goal_or(Rest).


dump_goal_and([[]]).
dump_goal_and([[A|Rest]]):- 
        dump_list_fluents([A]), 
        (Rest == [] -> 
           true;
           format(",",[])),
        dump_goal_and([Rest]). 

%remove_duplicates(L,L1) :- remove_dups(L,L1).

collect_depth(5).

dumpo(ACTIONS) :-
	option(Opt),
	collect_depth(Depth),
	findall(U,cpa_initially(cpa_oneof(U)),L11),
	(\+member(no_duals,Opt) -> filter_initial_duals(L11,L1); L1=L11),
	count_cases(L1,OrigCount),
	another_collect(L1,LIST,Depth,ACTIONS),
	compose_in(LIST,LIST1,1,FinalCount),
	retractall(dumpo_stats(_,_,_)),
	statistics(walltime,[_,T]),
	assert(dumpo_stats(OrigCount,FinalCount,T)),
	bubba,
	my_dump_oneof(LIST1).

bubba.

filter_initial_duals([],[]).
filter_initial_duals([L|Rest],[L1|Rest1]) :-
	simplify_duals(L,L1),
	filter_initial_duals(Rest,Rest1).

count_cases([],1).
count_cases([A|B],Count) :-
	count_cases(B,C1),
	length(A,C2),
	Count is C1*C2.


my_dump_oneof([]).
my_dump_oneof([A|B]) :-
	my_dump_oneof_a(A),
	my_dump_oneof(B).

my_dump_oneof_a(List) :-
	format("initially ",[]),
	my_dump_oneof(List,[]),
	format(";~n",[]).
my_dump_oneof([],_).
my_dump_oneof([L1|Rest],Gone) :-
	my_dump_one_case(L1,Rest,Gone),
	(Rest == [] -> true; format(" | ",[])),
	NewGone=[L1|Gone],
	my_dump_oneof(Rest,NewGone).

generate_constructs(Current, Prev, Next, Cases) :-
	append(Prev,Next,Others),
	create_cases(Others, Current, Cases).
create_cases([A],Current,Cases):- !,
	combine_cases(A,Current,Cases).
create_cases([A|B], Current, Cases) :-
	create_cases(B,Current, Cases1),
	combine_cases(A, Current, Cases2),
        compose_the_cases(Cases2,Cases1,Cases).
%	append(Cases1,Cases2,Cases).

compose_the_cases([],_,[]).
compose_the_cases([(Current,List1)|Rest], List2, List3) :-
	compose_the_cases( Rest, List2, List4),
	compose_one_of_the_cases(Current, List1, List2,List5),
	append(List4,List5,List3).
compose_one_of_the_cases(_Current,_List, [],[]).
compose_one_of_the_cases(Current,List,[(Current,Case)|Rest], Result) :-
	compose_one_of_the_cases(Current,List,Rest,Res1),
	(incompatible(List,Case) -> Result = Res1 ;
	    append(List,Case,Comp),
	    Result = [(Current,Comp)|Res1]).
incompatible(L1,L2) :-
	member(X,L1),
	flip_fluent(X,Y),
	member(Y,L2),!.
	

combine_cases(List, Current, Cases) :-
	merge_lists(Current,Current1),
	combine_cases1(List, Current1, Cases1),
	make_cases(Cases1, Current1, Cases).

make_cases([],_,[]).
make_cases([A|B], Current, [(Current,A)| Z] ) :-
	make_cases(B,Current,Z).

combine_cases1([],_,[[]]).
combine_cases1([A|B], Current, Cases) :-
	combine_cases1(B,Current, C1),
	(A = [_|_] -> multiply_cases(A, Current, C1, Cases); 
	    add_to_each_case(A, Current, C1, Cases)).
add_to_each_case(_,_,[],[]) :-!.
add_to_each_case(A,Current,L, L) :-
	member(A, Current),!.
add_to_each_case(A, Current, [X|Y], [ [A|X] | Z] ) :-
	add_to_each_case(A,Current,Y,Z).

multiply_cases([],_,_,[]).
multiply_cases([A|B], Current, Old, New) :-
	multiply_cases(B,Current, Old, New1),
	(member(A,Current) -> New = New1; 
	    add_to_each_case(A,Current,Old, New2),
	    append(New1,New2, New)).

my_dump_one_case(Current, Next,Past) :-
	generate_constructs(Current, Next, Past, Cases),
	process_constructs(Cases).

process_constructs([]).
process_constructs([(Pos,Neg)|Rest]) :-
	format("( ",[]),
	my_dump_list(Pos),
	(Neg = [] -> true; format(" , ",[]), my_dump_nlist(Neg)),
	format(" )",[]),
	(Rest = [] -> true; format(" | ",[])),
	process_constructs(Rest).

remove_done([],X,X).
remove_done([A|B], X, Y) :-
	(select(A,X,Z)->true; Z=X),
	remove_done(B,Z,Y).

remove_ndone([],X,X).
remove_ndone([A|B],X,Y) :-
	flip_literal(A,C),
	(select(C,X,Z) -> true; Z=X),
	remove_ndone(B,Z,Y).

%%%
my_dump_list1([A]) :- !,
	(A=[_|_] -> my_dump_list1(A);
	    (A=neg(F) -> format("-~q",[F]); 
		format("~q",[A]))).
my_dump_list1([A|B]) :-
	(A=[_|_] -> my_dump_list1(A);
	    (A=neg(F) -> format("-~q,",[F]); 
		format("~q,",[A]))),
	    my_dump_list1(B).


my_dump_nlist1([A]) :-!,
	(A=neg(F) -> format("~q",[F]);
	    format("-~q",[A])).
my_dump_nlist1([A|B]) :-
	(A=neg(F) -> format("~q,",[F]);
	    format("-~q,",[A])),
	    my_dump_nlist1(B).

%%%
my_dump_list([A]) :- !,
	(A=neg(F) -> format("-~q",[F]); 
	    format("~q",[A])).
my_dump_list([A|B]) :-
	(A=neg(F) -> format("-~q,",[F]); 
	    format("~q,",[A])),
	    my_dump_list(B).


my_dump_nlist([A]) :-!,
	(A=neg(F) -> format("~q",[F]);
	    format("-~q",[A])).
my_dump_nlist([A|B]) :-
	(A=neg(F) -> format("~q,",[F]);
	    format("-~q,",[A])),
	    my_dump_nlist(B).

my_dump_extract([],[]).
my_dump_extract([L|R],T) :-
	my_dump_extract(R,T1),
	(this_is_an_and_case(L) -> merge_lists(L,L1); L1=L),
	append(L1,T1,T).

compose_in([],[],X,X).
compose_in([A|B],[Goal|Remainder],CIn,Cout) :-
	find_all_independent(A,B,Indeps,Deps),!,
	length(Indeps,NI),
	compose_two(Indeps,Goal),
	count_combination(Indeps,CT),
	CIn1 is CIn*CT,
	compose_in(Deps,Remainder,CIn1,Cout).

count_combination([],0) :- !.
count_combination([[A,_]|B],Count) :-
	count_combination(B,C1),
	length(A,C2),
	(C1 > C2 -> Count = C1; Count=C2).

compose_two(Ind, Goal) :-
	clean_two(Ind, Ind1),
	construct_goal(Ind1,Goal).
construct_goal(Ind,[]) :-
	finished(Ind),!.
construct_goal(Ind,[G1|G]) :-
	one_goal_step(Ind,Ind1,[],G1x),
	remove_duplicates(G1x,G1),
	construct_goal(Ind1,G).
one_goal_step([],[],L,L).
one_goal_step([pu(X,[A|B])|Rest], [pu(X,B)|Rest1], L1,L) :- !,
	one_goal_step(Rest,Rest1,[A|L1],L).
one_goal_step([pu(X,[])|Rest], [pu(X,[])|Rest1], L1, L) :-
	one_goal_step(Rest,Rest1,[X|L1],L).



finished([]).
finished([pu(_,[])|Rest]) :-
	finished(Rest).

clean_two([],[]).
clean_two([[F,_A]|R], [pu(X,F)|R1]) :-
	F=[X|_],
	clean_two(R,R1).

find_all_independent(A,[],[A],[]).
find_all_independent([F,A], [[F1,A1]|R], R1, [[F1,A1]|R2]) :-
	(this_is_an_and_case(F) -> merge_lists(F,MerF); MerF=F),
	(this_is_an_and_case(F1) -> merge_lists(F1,MerF1); MerF1=F1),
	(member(X,MerF), member(X,MerF1); 
	    member(X,A), member(X,A1)),!,
	    find_all_independent([F,A], R,R1,R2).
find_all_independent([F,A], [[F1,A1]|R], [[F1,A1]|R1], R2) :-
	find_all_independent([F,A],R,R1,R2).

combine_two([F1,A1],[F2,A2], [NewF,NewA]) :-
	combine_two_fluents(F1,F2,NewF),
	append(A1,A2,NewA).


dump_initial(F,ACTIONS) :-
	option(Opt),
	findall(M,(cpa_initially(M),member(M,F)),List1),
	findall(neg(M1),(cpa_initially(neg(M1)), member(M1,F)),List2),
	append(List1,List2,List3),
	(\+member(no_duals,Opt) -> filter_duals(List3,List4); List3=List4),
        remove_duplicates(List4, List),
	dump_initial_sum(List),
	option(OPT),
	(\+member(no_oneof,OPT) -> dumpo(ACTIONS);
	    findall(Y, (cpa_initially(cpa_oneof(Y))), List4x),
	    remove_duplicates(List4x, List5x),
	    dump_initial_oneof(List5x)),
        findall(cpa_or(X,Y), (cpa_initially(cpa_or(X,Y))), List6),
        remove_duplicates(List6,List7), 
        dump_initial_or(List7).

blah.

filter_duals([],[]).
filter_duals([neg(A)|B], [C|B1]) :-
	duals(C,A),!,
	filter_duals(B,B1).
filter_duals([neg(A)|B], [neg(A)|B1]) :-
	!,
	filter_duals(B,B1).
filter_duals([A|B],[neg(C)|B1]) :-
	duals(C,A),!,
	filter_duals(B,B1).
filter_duals([A|B],[A|B1]) :-
	filter_duals(B,B1).

dump_initial_sum([]).

dump_initial_sum([A|B]) :-
	(always_true(L)->true; L=[]), member(A,L),!,
        dump_initial_sum(B).

dump_initial_sum([A|B]) :-
	(always_false(L)->true; L=[]), member(A,L),!,
	dump_initial_sum(B).


dump_initial_sum([neg(A)|B]) :-
	(always_true(L)->true; L=[]), member(A,L),!,
        dump_initial_sum(B).

dump_initial_sum([neg(A)|B]) :-
	(always_false(L)->true; L=[]), member(A,L),!,
	dump_initial_sum(B).


dump_initial_sum([A|B]) :-
        fluent(A), 
	format("initially ~q;~n",[A]),
	dump_initial_sum(B).
dump_initial_sum([neg(A)|B]) :-
        fluent(A), 
	format("initially -~q;~n",[A]),
	dump_initial_sum(B).

dump_initial_oneof([]). 
dump_initial_oneof([L|Rest]):-
        dump_init_one(L), 
        dump_initial_oneof(Rest). 

dump_init_one(L) :-
	length(L,2),
	duals(A,B), 
	member(A,L), member(B,L),
	format("initially ~q | -~q;~n",[A,neg(A)]),!.
dump_init_one(L) :-
	this_is_an_and_case(L),!,
	findall((X,Y), (member(X,L), delete(L,X,Y)), Z),
	format("initially ",[]),
	dump_one_of_and(Z),
	format(";~n",[]).
dump_init_one(L):-
        findall((X,Y), (member(X,L), delete(L,X,Y)), Z),
        format("initially ",[]),         
        dump_one_of(Z), 
        format(";~n",[]).

this_is_an_and_case(List) :-
	member([_|_], List),!.


dump_one_of_and([]).
dump_one_of_and([(X,Y)|Rest]) :-
	format("(",[]),
	dump_XY_and(X,Y),
	format(")",[]),
	(Rest=[] -> true; format("|",[])),
	dump_one_of_and(Rest).

dump_one_of([]).
dump_one_of([(X,Y)|Rest]):- 
        format("(",[]),         
        dump_XY(X,Y), 
        format(")",[]), 
        (Rest = [] -> true; format("|",[])), 
        dump_one_of(Rest).

dump_XY_and(X,Y) :-
	dump_XY_and_pos(X),
	dump_XY_and_neg(Y,X).

dump_XY_and_pos([]).
dump_XY_and_pos([A|B]) :-
	fluent(A), format("~q,",[A]),
	dump_XY_and_pos(B).
dump_XY_and_pos([neg(A) | B]) :-
	fluent(A), format("-~q,",[A]),
	dump_XY_and_pos(B).

dump_XY(X, Y):- 
        fluent(X), format("~q,",[X]),
        dump_neg_list_XY(Y). 

dump_XY(neg(X), Y):- 
        fluent(X), format("-~q,",[X]),
        dump_neg_list_XY(Y). 

dump_XY_and_neg([],_).
dump_XY_and_neg([A|B],Done) :-
	sub_dump_XY_and_neg(A,Done),
	(B=[]->true; format(",",[])),
	dump_XY_and_neg(B,Done).
sub_dump_XY_and_neg([],_).
sub_dump_XY_and_neg([A|B],Done) :-
	fluent(A), \+member(A,Done),
	format("-~q",[A]),
	(B=[] -> true; format(",",[])),
	sub_dump_XY_and_neg(B,Done).
sub_dump_XY_and_neg([neg(A)|B],Done) :-
	fluent(A), \+member(neg(A),Done),
	format("~q",[A]),
	(B=[] -> true; format(",",[])),
	sub_dump_XY_and_neg(B,Done).


dump_neg_list_XY([]).
dump_neg_list_XY([X|Rest]):-
        fluent(X), format("-~q",[X]),
        (Rest = [] -> true; format(",",[])), 
        dump_neg_list_XY(Rest).
dump_neg_list_XY([neg(X)|Rest]):-
        fluent(X), format("~q",[X]),
        (Rest = [] -> true; format(",",[])), 
        dump_neg_list_XY(Rest).
             
dump_initial_or([]).
dump_initial_or([L1|Rest]):-
        findall(X, (cv_and(L1, L2), member(X, L2)), L), 
        (L == [] ->
            true;
            format("initially ",[])
        ),
        dump_init_oneof(L),
        dump_initial_or(Rest).

dump_init_oneof([]).
dump_init_oneof([A|B]):-
        dump_list_fluents([A]),
        (B == [] -> 
           format(";~n",[]); 
           format(" | ",[])
        ), 
        dump_init_oneof(B).

dump_fluents([],_).
dump_fluents([A|B],In):-
	\+(A=neg(_)),
	(always_true(AT)->true; AT=[]),
	member(A,AT),!,
	dump_fluents(B,In).

dump_fluents([A|B],In):-
	\+(A=neg(_)),
	(always_false(AF)->true; AF=[]),
	member(A,AF),!,
	dump_fluents(B,In).

dump_fluents([A|B],In) :-
	A = neg(_), !,
        dump_fluents(B,In).
dump_fluents([A|B],In) :-
	duals(C,A),!,
	(member(C,In) -> true;
	    format("fluent ~q;~n",[C])),
	dump_fluents(B,[C|In]).
dump_fluents([A|B],In) :-
	format("fluent ~q;~n",[A]),
	dump_fluents(B,[A|In]).

dump_actions([]).
dump_actions([A|Rest]) :-
	format("action ~q;~n",[A]),
	dump_actions(Rest).

dump_executable([]).
dump_executable([A|Rest]) :-
	findall((A,L1), (cpa_executable(A,L1), \+(L1==[])), LExecs), 
        dump_execs(LExecs), 
        dump_executable(Rest). 

dump_execs([]).
dump_execs([(A,Conds)|Rest]):-
        (always_true(AT)->true; AT=[]),
        (always_false(AF)->true; AF=[]),
        simplify(Conds, AT, AF, NConds), 
        ( NConds == [] -> true;
          format("executable ~q if ",[A]), 
          dump_list_fluents(NConds), 
          format(";~n",[])
        ),
        dump_execs(Rest).


dump_list_fluents(L) :-
	option(Opt),
	(\+member(no_duals,Opt) -> simplify_duals(L,L1); L=L1),
	dump_list_fluents1(L1).
simplify_duals(L,L1) :-
	replace_with_dual(L,L2),
	remove_duplicates(L2,L1).
replace_with_dual([],[]).
replace_with_dual([neg(A)|B],[A1|B1]) :-
	duals(C,A), !,
	A1=C,
	replace_with_dual(B,B1).
replace_with_dual([neg(A)|B], [neg(A)|B1]) :-
	!,
	replace_with_dual(B,B1).
replace_with_dual([A|B],[neg(C)|B1]) :-
	duals(C,A),!,
	replace_with_dual(B,B1).
replace_with_dual([A|B],[A|B1]) :-
	replace_with_dual(B,B1).

dump_list_fluents1([]).
dump_list_fluents1([A|B]):-
%        fluent(A),  
	\+ (A=neg(_)),
        (B == [] -> 
  	   format(" ~q",[A]);
           format(" ~q,",[A]),   
  	   dump_list_fluents1(B)
        ).
dump_list_fluents1([neg(A)|B]):-
%        fluent(A),  
        (B == [] -> 
  	   format(" -~q",[A]);
           format(" -~q,",[A]),   
	  dump_list_fluents1(B)
        ).

simplify(Conds, AT, AF, NConds):-
        findall(X, (member(X,Conds), member(X,AT), \+unknown(X)), ATConds),
        findall(neg(Y), (member(neg(Y),Conds), member(Y,AF), \+unknown(Y)), AFConds),
        findall(L, (member(L,Conds), \+(member(L,ATConds)), \+(member(L,AFConds))), NConds).

bah.

dump_action_effects([], _).
dump_action_effects([A|Rest], Fluents):-
	findall((A,E,L), (cpa_causes(A,E,L)), LEffects),
	process_effects_duals(LEffects,LEffects1),
        dump_effects(LEffects1, Fluents),
        dump_action_effects(Rest, Fluents).


process_effects_duals(LIn, LOut) :-
	substitute_duals(LIn, LIn1),
	remove_equivalent(LIn1,LIn2),
	combine_conditions(LIn2,LOut).

substitute_duals([],[]).
substitute_duals([(A,E,L)| Rest] , [(A,E1,L1) | Rest1]) :-
	simplify_duals(E,E1),
	simplify_duals(L,L1),
	substitute_duals(Rest,Rest1).
remove_equivalent([],[]).
remove_equivalent([(A,E,L) | Rest] , Rest1) :-
	equivalent_effect((A,E,L), Rest),!,
	remove_equivalent(Rest,Rest1).
remove_equivalent([(A,E,L) | Rest], [(A,E,L)|Rest1]) :-
	remove_equivalent(Rest,Rest1).
equivalent_effect((A,E,L), [(A,E1,L1)|_]) :-
	subset_list(E,E1), subset_list(E1,E),
	subset_list(L,L1), subset_list(L1,L),!.
equivalent_effect((A,E,L), [_|Rest]) :-
	equivalent_effect((A,E,L), Rest).
subset_list(L,L1) :-
	findall(X, (member(X,L),\+member(X,L1)), []).
combine_conditions(L,L). %%%%%%%%%%%%%%%%% TO BE IMPLEMENTED

	



dump_effects([], _).
dump_effects([(A,E,Conds)|Rest], Fluents):-
        (always_true(AT)->true; AT=[]),
        (always_false(AF)->true; AF=[]),
        (reachable(Conds, AT, AF, Fluents) -> 
           (
            simplify(Conds, AT, AF, NConds),
            (
              NConds == [] -> 
                dump_effect(A,E);
                dump_effect(A,E,NConds)
            )
           ) 
           ;
           true
        ),
        dump_effects(Rest, Fluents).

dump_effect(A,E):-
        format("~q causes ",[A]),
        dump_list_fluents(E), 
        format(";~n",[]). 

dump_effect(A,E,Conds):-
        format("~q causes ",[A]),
        dump_list_fluents(E), 
        format(" if ", []),
        dump_list_fluents(Conds), 
        format(";~n",[]). 

reachable([], _,_,_).
reachable([F|Rest], AT, AF, Fluents):-
        fluent(F),
        member(F, Fluents), 
        \+ member(F, AF), 
        reachable(Rest, AT, AF, Fluents).
reachable([neg(F)|Rest], AT, AF, Fluents):-
        fluent(F),
        member(F, Fluents), 
        \+ member(F, AT), 
        reachable(Rest, AT, AF, Fluents).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% cv_and(Input, Output)

convert_executable :- 
	findall([executable(Action,Condition),Body], clause(executable(Action,Condition),Body), Exes),
	convert_executable(Exes).
convert_executable([]).
convert_executable([ [executable(Action,[]),Body] | Rest ]) :-
	(assert((cpa_executable(Action,[]):-Body)), fail; true),
	convert_executable(Rest).

convert_executable([ [executable(Action,[Condition]),Body1] | Rest ]) :-
	(cv_and(Condition,NewConds1),
            process_equal(NewConds1, NewConds, NewBody),
            assert(:-(cpa_executable(Action,NewConds), (Body1,NewBody))), fail; true),
	convert_executable(Rest).

process_equal([], [], true).
process_equal([cpa_equal(X,Y)|Rest], NewCond, (cpa_equal(X,Y),NewBody)):- !,
       process_equal(Rest, NewCond, NewBody).
process_equal([neg(cpa_equal(X,Y))|Rest], NewCond,(\+(cpa_equal(X,Y)),NewBody)):- !,
       process_equal(Rest, NewCond, NewBody).
process_equal([Z|Rest], [Z|NewCond], NewBody):- !,
       process_equal(Rest, NewCond, NewBody).

cpa_equal(X,X).

convert_causes:-
        findall([causes(Action,Effect),Body], clause(causes(Action,Effect,[]),Body), LCauses),
        convert_causes(LCauses).

convert_causes([]).
convert_causes([[causes(Action,[Effect]),Body] | Rest]) :- 
        (cv_when(Effect, Condition, NewEffect),
            assert((cpa_causes(Action, NewEffect,Condition):-Body)), fail; true), 
        convert_causes(Rest).

convert([Input], Output) :-
  findall(O, cv_and(Input,O), Output).

cv_and(Input, [Input]) :- 
   functor(Input, F, _N), \+(F==cpa_and), \+(F==cpa_or), \+(F==cpa_when).
cv_and(cpa_and(X), Y) :-
  !, cv_and(X,Y).
cv_and(cpa_and(X,Y), Z) :- 
  !, cv_and(X,Z1),
  cv_and(Y,Z2),
  append(Z1,Z2,Z).
cv_and(cpa_or(X), Y) :-
  !, cv_and(X,Y).
cv_and(cpa_or(X,Y), Z) :-
  (cv_and(X,Z); cv_and(Y,Z)).

/* base */
cv_when(cpa_when(X,Y), Z1, Z2):-
  cv_and(X,Z1), cv_and(Y, Z2).

/* no condition */

cv_when(cpa_and(X), [], Z):-
  functor(X, F, _N), \+(F==cpa_when), 
  cv_and(X, Z).

cv_when(cpa_and(X), Y, Z):-
  functor(X, F, _N), F==cpa_when, 
  cv_when(X, Y, Z).

cv_when(cpa_and(X,Y), [], Z):-
  functor(Y, F, _N), \+(F==cpa_when), 
  no_more_when(X,Y),
  cv_and(cpa_and(X,Y), Z).

cv_when(cpa_and(X,Y), Cond , Cons) :-
  functor(Y, F, _N), \+(F==cpa_when), 
  \+(no_more_when(X,Y)),
  (cv_when(X,Cond,Cons); 
      cv_and(Y,Cons), Cond=[]).

cv_when(cpa_and(X,Y), Z1, Z2):-
  functor(Y, F, _N), F==cpa_when, 
  (cv_when(X, Z1, Z2); 
    cv_when(Y, Z1, Z2)).

no_more_when(X,Y) :-
	no_more_when(X),
	no_more_when(Y).

no_more_when(cpa_and(X)) :- !,
	no_more_when(X).
no_more_when(cpa_and(X,Y)) :- !,
	no_more_when(X),
	no_more_when(Y).
no_more_when(X) :-
	functor(X,F,_), \+(F == cpa_when).


%% cpa_or(cpa_or(neg(cpa_high(cpa_l1))),cpa_high(cpa_l1))

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%% given a list of oneofs
%% 

another_collect([],[],_,_).
another_collect([L|Rest],[ [L,Acts] | Rest1],N,ACTIONS) :-
	another_collect(Rest,Rest1,N,ACTIONS),
	collect1(L,A1,N,ACTIONS),
	remove_duplicates(A1,Acts).


%%

merge_lists([],[]).
merge_lists([A|B], C) :-
	merge_lists(B,B1),
	(A = [_|_] -> 	append(A,B1,C); C=[A|B1]).

collect1(List,LF,N,ACTIONS):-
	(this_is_an_and_case(List) -> merge_lists(List,List1); List1=List),
	findall(A, (member(A,ACTIONS), member(F,List1), (cpa_causes(A,_,PF);cpa_executable(A,PF)),member(F,PF)), LF1),
	collects(LF1,LF,N,ACTIONS).

collects(LA,LA,0,_) :- !.
collects(Acts, LA, N,ACTIONS):-
   findall(E, (member(A,Acts),cpa_causes(A, Effects, _),  member(E, Effects)), LE), 
   list_to_ord_set(LE,SE),
   findall(NA, (member(NA,ACTIONS),\+member(NA,Acts), needs_some(NA,SE)), LA2),
   append(Acts,LA2,LA1),
   N1 is N-1,
   collects(LA1, LA, N1,ACTIONS).

needs_some(NA,SE):-
   (cpa_causes(NA, _, Conds);cpa_executable(NA,Conds)),
   list_to_ord_set(Conds,SC),
   ord_intersect(SE,SC).


%%%

is_disjoint(LF,LG):-
   list_to_ord_set(LF,SF),
   list_to_ord_set(LG,SG),
   ord_disjoint(SF,SG).

independent(F,G,N):-
   collect(F,LF,N),
   collect(G,LG,N),
   is_disjoint(LF,LG).

test_independent(F,G,N):-
   independent(F,G,N).

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
