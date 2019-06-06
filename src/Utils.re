open AppState;

let allRepsAreEqual = (sets: array(set)): bool =>
  sets->Belt.Array.every(s => s.reps === Belt.Array.getExn(sets, 0).reps);

let formatSetsReps = (sets: array(set)): string =>
  (sets |> Belt.Array.length |> string_of_int)
  ++ "x"
  ++ (Belt.Array.getExn(sets, 0).reps |> string_of_int);

let formatCustomSets = (sets: array(set)): string =>
  sets
  ->Belt.Array.map(s => s.reps)
  ->Belt.Array.reduce("", (acc, value) =>
      switch (acc) {
      | "" => string_of_int(value)
      | formatttedSets => formatttedSets ++ "-" ++ string_of_int(value)
      }
    );

// TODO: consolidate functions
let formatDialogSetsReps = (dialogState: dialogState): string =>
  dialogState.inputMode == Standard
    ? string_of_int(dialogState.numberOfSets)
      ++ "x"
      ++ string_of_int(dialogState.numberOfReps)
    : dialogState.customSets |> formatCustomSets;

let getSetsFromSetsReps = dialogState =>
  Array.make(
    dialogState.numberOfSets,
    {reps: dialogState.numberOfReps, rpe: None},
  );

let getSetsArray = (dialogState: dialogState): array(set) =>
  dialogState.inputMode == Custom
    ? dialogState.customSets : getSetsFromSetsReps(dialogState);

let formatSets = (sets: array(set)): string =>
  switch (sets) {
  | [||] => ""
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
  validRpeValues->Belt.List.some(r => r == value);

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
