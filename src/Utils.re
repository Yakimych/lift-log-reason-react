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

let numberToDateString = (number: int) =>
  (number < 10 ? "0" : "") ++ string_of_int(number);

let toCustomDateFormat = (date: Js.Date.t): string => {
  let year = date |> Js.Date.getFullYear |> truncate |> string_of_int;
  let month =
    date |> Js.Date.getMonth |> truncate |> (+)(1) |> numberToDateString;
  let day = date |> Js.Date.getDate |> truncate |> numberToDateString;

  year ++ "-" ++ month ++ "-" ++ day;
};

let toMaybeFloat = (floatString: string): option(float) =>
  try (Some(floatString |> float_of_string)) {
  | _ => None
  };

let toMaybeInt = (intString: string): option(int) =>
  try (Some(intString |> int_of_string)) {
  | _ => None
  };

let validRpeValues = [6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0];
let isValidRpe = (value: float): bool =>
  validRpeValues |> List.exists(r => r == value);

let toValidRpe = (rpeString: string): option(float) => {
  let maybeRpeFloat = rpeString |> toMaybeFloat;
  let maybeValid = Belt.Option.map(maybeRpeFloat, isValidRpe);
  switch (maybeValid) {
  | Some(true) => maybeRpeFloat
  | _ => None
  };
};

let toValidSet = (setString: string): option(set) => {
  let stringParts = Js.String.split("@", setString);

  switch (stringParts) {
  | [|repsString|] =>
    Belt.Option.map(repsString |> toMaybeInt, r => {reps: r, rpe: None})
  | [|repsString, rpeString|] =>
    let maybeRpe = rpeString |> toValidRpe;
    Belt.Option.map(repsString |> toMaybeInt, r => {reps: r, rpe: maybeRpe});
  | _ => None
  };
};
