# Election

In this project, we created an electronic voting system

![image](https://user-images.githubusercontent.com/72739568/124252704-e6f9ab80-db2f-11eb-8209-67246b3591e9.png)

### **Class Definitions:** ###

* Citizen - Every citizen has a name and an ID, and the district in which the citizen can vote.

* District - Each district has a list of citizens who can vote and a list of elected officials. The identity of the voters in each district is determined by the ratio of votes each party received.

* Party - Each party has a candidate and the list of electors is sorted by the district to which the electors are nominated.

* Divided District - A district that nominates its presidential candidates according to the ratio of votes.

* United District - A district that gives all its representatives to the candidate of the party that won the most votes in the District.
  
  Both Divided District and Divided District are inherited from District.

* Election - each election has a list of voters (citizens), a list of districts, and a list of parties.

* Normal Election - election with more than one district, the results are calculated in each district according to its type

* Simple Election - election without districts, the results are calculated according to the ratio of votes.

  Both Simple Election and Normal Election are inherited from the election.

## The project made by:
- Leead Arbetman
- Tomer Ahimeir
