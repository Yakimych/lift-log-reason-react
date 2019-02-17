open Jest;
open Expect;
open AppReducer;
open AppActions;
open AppState;

let runActions = actions =>
  actions |> List.fold_left(appReducer, InitialState.getInitialState());

describe("AppReducer", () => {
  describe("number of sets", () => {
    test("should be parsed correctly for a valid int", () => {
      let finalState = [DialogOpen, SetNumberOfSets("1")] |> runActions;

      expect(finalState.dialogState.numberOfSets) |> toBe(1);
    });

    test("should be changed correctly when input is a valid int", () => {
      let finalState =
        [DialogOpen, SetNumberOfSets("1"), SetNumberOfSets("12")]
        |> runActions;

      expect(finalState.dialogState.numberOfSets) |> toBe(12);
    });

    test("should not be changed when input is an invalid int", () => {
      let finalState =
        [
          DialogOpen,
          SetNumberOfSets("1"),
          SetNumberOfSets("12"),
          SetNumberOfSets("12a"),
        ]
        |> runActions;

      expect(finalState.dialogState.numberOfSets) |> toBe(12);
    });
  });

  describe("custom sets", () => {
    test("should be changed correctly without RPE at index 0", () => {
      let finalState =
        [DialogOpen, SetInputMode(CustomReps), ChangeCustomSet(0, "1")]
        |> runActions;

      expect(finalState.dialogState.customSets |> Belt.List.head)
      |> toEqual(Some({reps: 1, rpe: None}));
    });

    test("should be changed correctly with RPE at index 1", () => {
      let finalState =
        [DialogOpen, SetInputMode(CustomReps), ChangeCustomSet(1, "4@7.5")]
        |> runActions;

      expect(List.nth(finalState.dialogState.customSets, 1))
      |> toEqual({reps: 4, rpe: Some(7.5)});
    });
  });
});
