# Single-Agent Epistemic Planner

Single-Agent Planner is a complete epistemic planner without the epistemic closed world assumption for single agent which is logic-based. 

## Overview
This programme is a part of the reasearch on single-agent planner, and the research paper was published on [IJCAI 2015](http://www.aaai.org/ocs/index.php/IJCAI/IJCAI15/paper/view/11109/11117).

Intuitively, the planner provide an agent with a series of algorithms so that the agent can interact with the enviroment, tack actions and get to the goal. BTW, all these are done in your copmuter, instead of entity.

## Programme Structure
This planner could be divided into three parts:
![](https://github.com/fangbq/SingleAgentPlanner/blob/master/img/Single-Agent%20Planner.png?raw=true)

#### 1. Parsing
This part, also called preprocess, contains three subtasks:

###### a) Parse - recognize and match the strings of epddl files

###### b) Store - pass tokens to an intermediate structure

###### c) Convert - convert intermediate structure to final structrue to be used to do planning
 
`Parser` is to parse the input files in epddl language(based on [pddl](https://en.wikipedia.org/wiki/Planning_Domain_Definition_Language), which contains the infos of defined actions that agent can do, initial state and goal state), and save the tokens from parser to our final data structure, stored in `Initial`. The intermediate structure `Reader` aims to simplify the code in `Initial` and make the transformation of structure more clear.

#### 2. Reasoning and Progression
Reasoning part contatins some reasoning algorithms of EDNF and ECNF(EDNF and ECNF both are epistemic formulas defined in that paper), those algorithms help agent to tell whether it can do any actions based on its current knowledge base.

Progression part helps agent update its knowledge base after an action completed.


#### 3. Planning
The main planning algorithm is PrAO algorithm [To et al., 2011](http://www.aaai.org/ocs/index.php/ICAPS/ICAPS10/paper/view/1461). The algorithm is based on progression and entailment which have been introduced in the last section.


## Example

### 1. Description
Consider the following example. *There is a room with a light in it. The agent stands out of the room, and it has a intial knowledge base which are some reasoning rules, such as if door open, then somebody in room, light off means nobody in room, and so on... The agent can do three actions defined as `senseL`(sense if the light on), `senseD`(sense if door open) and `knock`(knock the door). Its goal is to get to know if there any people in room.*


### 2. //todo
		
