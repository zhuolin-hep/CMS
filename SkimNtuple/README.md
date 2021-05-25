# An Introduction to the `SkimNtuple` Toolkit

`ntupleReducer.cc` is used to skim `TTree`s. This macro used `TTreeReader` to transform the `std::vector` stored in `TBranch`s to `float` and cut the `TTree`.

In the `reduceByRDataFrame` folder, the `ntuple_reducer.cc` is used to skim `TTree`s. This macro used `TTreeReader` to transform the `std::vector` stored in `TBranch`s to `float`. In other words, transform the `TTree` to a flat `TTree`. Then `RDataFrame` helps us select events in the flat `TTree`. But we found that the `RDataFrame` can't cut a `TTree` which is not flat. Because the `RDataFrame` is much faster than `TTreeReader`, we still wait and see whether the `RDataFrame` can cut the "unflat" `TTree`. `ntuple_reader.py` helps us transform `TBranch`s in the `TTree` to `TH1`s. But the new plot macro in `ZH` can plot `TTree` directly. 

`SE2T3` is a useful tool that copies `.root` files from T2 to my T3. We can run `python3 T22T3.py --mode 1,2,3,4` to use different functions. The script can check the result of a CRAB job (has output files or not), copy files from T2 to T3, generate `HTCondor` bash scripts, and `hadd` `.root` files. The scripts in the `Tools` subfolder can be executed independently.

`GenerateReduceScript.py` can generate `HTCondor` bash scripts to execute `ntuple_reducer.cc`. 