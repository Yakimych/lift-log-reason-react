open Jest;
open Expect;
open AppReducer;
open AppActions;
open AppState;

let runActions = actions =>
  actions->Belt.List.reduce(InitialState.getInitialState(), appReducer);

describe("AppReducer", () =>
  describe("links", () => {
    test("should be added", () => {
      let finalState = [DialogOpen, AddLink, AddLink, AddLink] |> runActions;
      expect(finalState.dialogState.links->Belt.Array.length) |> toBe(3);
    });

    test("should not be possible to add more than 3 links", () => {
      let finalState =
        [DialogOpen, AddLink, AddLink, AddLink, AddLink] |> runActions;
      expect(finalState.dialogState.links->Belt.Array.length) |> toBe(3);
    });

    test("should not be possible to remove link if none exist", () => {
      let finalState = [DialogOpen, RemoveLink(0)] |> runActions;
      expect(finalState.dialogState.links->Belt.Array.length) |> toBe(0);
    });

    test("should not be possible to remove more links than added", () => {
      let finalState =
        [
          DialogOpen,
          AddLink,
          AddLink,
          RemoveLink(1),
          RemoveLink(0),
          RemoveLink(0),
        ]
        |> runActions;
      expect(finalState.dialogState.links->Belt.Array.length) |> toBe(0);
    });

    test("should change text and url", () => {
      let linkText = "testLink1";
      let linkUrl = "testUrl1";
      let finalState =
        [
          DialogOpen,
          AddLink,
          AddLink,
          AddLink,
          ChangeLinkUrl(0, linkUrl),
          ChangeLinkText(0, linkText),
        ]
        |> runActions;

      let changedLink = finalState.dialogState.links->Belt.Array.getExn(0);
      expect((changedLink.text, changedLink.url))
      |> toEqual((linkText, linkUrl));
    });
  })
);
