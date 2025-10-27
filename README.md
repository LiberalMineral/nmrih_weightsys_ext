# API
native bool SetPlayerWeightByIdx(int player_idx,float weight);
# Attention
This extension sets every player's weight to 1000 by default.

Convar inv_maxcarry will not work.
BUT,to avoid client rendering issues and uncorrect client movement predication,you must call SendConVarValue(playerentidx,"inv_maxcarry",weights) after calling setweight.
# TODO
overhaul the codes...
