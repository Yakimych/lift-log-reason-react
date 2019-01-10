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

let formatSets = (sets: list(set)): string =>
  if (allRepsAreEqual(sets)) {
    (sets |> List.length |> string_of_int)
    ++ "x"
    ++ (List.hd(sets).reps |> string_of_int);
  } else {
    sets
    |> List.map(s => s.reps)
    |> List.fold_left(
         (acc, value) =>
           switch (acc) {
           | "" => string_of_int(value)
           | other => other ++ "-" ++ string_of_int(value)
           },
         "",
       );
  };