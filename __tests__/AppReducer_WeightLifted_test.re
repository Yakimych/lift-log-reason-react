open Jest;
open Expect;
open AppReducer;
open AppActions;
open AppState;

let runActions = actions =>
  actions |> List.fold_left(appReducer, InitialState.getInitialState());

describe("AppReducer", () =>
  describe("weightLifted", () => {
    test("should be parsed correctly for a valid float", () => {
      let finalState = [ChangeWeightLifted("1")] |> runActions;

      expect(finalState.newEntryState.weightLifted) |> toBe(1.0);
    });

    test("should be parsed correctly for a temporary float", () => {
      let finalState =
        [ChangeWeightLifted("1"), ChangeWeightLifted("1.")] |> runActions;

      expect(finalState.newEntryState.weightLifted) |> toBe(1.0);
    });

    test(
      "should be parsed correctly for a valid float with decimal separator", () => {
      let finalState =
        [
          ChangeWeightLifted("1"),
          ChangeWeightLifted("1."),
          ChangeWeightLifted("1.2"),
        ]
        |> runActions;

      expect(finalState.newEntryState.weightLifted) |> toBe(1.2);
    });

    test("should be unchanged when input is an invalid float", () => {
      let finalState =
        [DialogOpen, SetNumberOfSets("1"), SetNumberOfSets("1a")]
        |> runActions;

      expect(finalState.dialogState.numberOfSets) |> toBe(1);
    });
  })
);
