open Jest;
open Expect;
open AppReducer;
open AppActions;

let runActions = actions =>
  actions |> List.fold_left(appReducerFunc, InitialState.getInitialState());

describe("AppReducer", () => {
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
  });

  describe("links", () => {
    test("should be added", () => {
      let finalState = [DialogOpen, AddLink, AddLink, AddLink] |> runActions;
      expect(finalState.dialogState.links |> List.length) |> toBe(3);
    });

    test("text should be changed correctly", () => {
      let linkText = "testLink1";
      let finalState =
        [DialogOpen, AddLink, ChangeLinkText(0, linkText)] |> runActions;
      expect((finalState.dialogState.links |> List.hd).text)
      |> toBe(linkText);
    });
  });
});