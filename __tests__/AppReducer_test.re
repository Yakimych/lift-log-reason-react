open Jest;
open Expect;
open AppReducer;
open AppActions;

let runActions = actions =>
  actions |> List.fold_left(appReducerFunc, InitialState.getInitialState());

describe("AppReducer", () => {
  test("dialog should be closed from the start", () => {
    let initialState = InitialState.getInitialState();

    expect(initialState.dialogState.isOpen) |> toBe(false);
  });

  test("dialog should be open after DialogOpen is dispatched", () => {
    let finalState = [DialogClose, DialogOpen] |> runActions;

    expect(finalState.dialogState.isOpen) |> toBe(true);
  });

  test("dialog should be closed after DialogClose is dispatched", () => {
    let finalState = [DialogOpen, DialogClose] |> runActions;

    expect(finalState.dialogState.isOpen) |> toBe(false);
  });
});
