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
    test(
      "should be initialized with number of Sets when switching mode for the first time",
      () => {
        let finalState =
          [DialogOpen, SetNumberOfSets("6"), SetInputMode(CustomReps)]
          |> runActions;

        expect(finalState.dialogState.customSets |> Belt.List.length)
        |> toEqual(6);
      },
    );

    test(
      "should be initialized with values of Reps when switching mode for the first time",
      () => {
        let finalState =
          [DialogOpen, SetNumberOfReps("8"), SetInputMode(CustomReps)]
          |> runActions;

        expect(
          finalState.dialogState.customSets->Belt.List.every(e => e.reps == 8),
        )
        |> toBe(true);
      },
    );

    test(
      "should not rewrite CustomSets when switching InputMode after manual edit",
      () => {
      let finalState =
        [
          DialogOpen,
          SetNumberOfSets("6"),
          SetNumberOfReps("8"),
          SetInputMode(CustomReps),
          ChangeCustomSet(0, "2@9.5"),
          SetInputMode(SetsReps),
          SetInputMode(CustomReps),
        ]
        |> runActions;

      expect(finalState.dialogState.customSets |> Belt.List.head)
      |> toEqual(Some({reps: 2, rpe: Some(9.5)}));
    });

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

    test("should not be able to add more than 30 custom sets", () => {
      let add31CustomSets = Array.make(31, AddCustomSet) |> Array.to_list;
      let finalState =
        [DialogOpen, SetInputMode(CustomReps)]
        @ add31CustomSets
        |> runActions;

      expect(finalState.dialogState.customSets |> List.length) |> toEqual(30);
    });

    test("should not be able to delete last custom set", () => {
      let remove10CustomSets =
        Array.make(10, RemoveCustomSet(0)) |> Array.to_list;
      let finalState =
        [DialogOpen, SetInputMode(CustomReps)]
        @ remove10CustomSets
        |> runActions;

      expect(finalState.dialogState.customSets |> List.length) |> toEqual(1);
    });

    test("added custom set should be the same as last custom set", () => {
      let finalState =
        [
          DialogOpen,
          SetInputMode(CustomReps),
          ChangeCustomSet(2, "8"),
          AddCustomSet,
        ]
        |> runActions;

      expect(finalState.dialogState.customSets |> List.rev |> List.hd)
      |> toEqual({reps: 8, rpe: None});
    });
  });
});
