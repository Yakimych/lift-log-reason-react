open Jest;
open Expect;
open AppReducer;
open AppActions;

describe("AppReducer", () => {
  test("dialog should be closed from the start", () => {
    let initialState = InitialState.getInitialState();

    expect(initialState.dialogState.isOpen) |> toBe(false);
  });

  test("dialog should be open after DialogOpen is dispatched", () => {
    let initialState = InitialState.getInitialState();
    let actions = [DialogClose, DialogOpen];

    let finalState = actions |> List.fold_left(appReducerFunc, initialState);

    expect(finalState.dialogState.isOpen) |> toBe(true);
  });

  test("dialog should be closed after DialogClose is dispatched", () => {
    let initialState = InitialState.getInitialState();
    let actions = [DialogOpen, DialogClose];

    let finalState = actions |> List.fold_left(appReducerFunc, initialState);

    expect(finalState.dialogState.isOpen) |> toBe(false);
  });
});
