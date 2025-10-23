# API
native bool SetPlayerWeightByIdx(int idx,float weight);
# Attention
To avoid client rendering problem,call SendConVarValue(entidx,"inv_maxcarry",weights) after setweight.
