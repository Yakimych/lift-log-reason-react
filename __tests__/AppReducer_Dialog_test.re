open Jest;
open Expect;
open AppReducer;
open AppActions;
open AppState;

let runActions = actions =>
  actions |> List.fold_left(appReducer, InitialState.getInitialState());

describe("AppReducer", () =>
  describe("dialog", () => {
    test("should be closed from the start", () => {
      let initialState = InitialState.getInitialState();

      expect(initialState.dialogState.isOpen) |> toBe(false);
    });

    test("should be open after DialogOpen is dispatched", () => {
      let finalState = [DialogClose, DialogOpen] |> runActions;

      expect(finalState.dialogState.isOpen) |> toBe(true);
    });

    test("should be closed after DialogClose is dispatched", () => {
      let finalState = [DialogOpen, DialogClose] |> runActions;

      expect(finalState.dialogState.isOpen) |> toBe(false);
    });
  })
);
