open AppState;

let removeAtIndex = (index, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.filter(t => t |> fst != index)
  |> List.map(t => t |> snd);

let changeAtIndex = (index, replaceFunc, newValue, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.map(t =>
       if (t |> fst == index) {
         t |> snd |> replaceFunc(newValue);
       } else {
         t |> snd;
       }
     );

let replaceFunc = (newValue, _) => newValue;

let allRepsAreEqual = (sets: list(set)): bool =>
  sets |> List.for_all(s => s.reps === List.hd(sets).reps);

let formatSetsReps = (sets: list(set)): string =>
  (sets |> List.length |> string_of_int)
  ++ "x"
  ++ (List.hd(sets).reps |> string_of_int);

let formatCustomSets = (sets: list(set)): string =>
  sets
  |> List.map(s => s.reps)
  |> List.fold_left(
       (acc, value) =>
         switch (acc) {
         | "" => string_of_int(value)
         | formatttedSets => formatttedSets ++ "-" ++ string_of_int(value)
         },
       "",
     );

let formatSets = (sets: list(set)): string =>
  switch (sets) {
  | [] => ""
  | list =>
    list |> (list |> allRepsAreEqual ? formatSetsReps : formatCustomSets)
  };
