open Jest;
open Expect;
open AppReducer;
open AppActions;
open AppState;

let runActions = actions =>
  actions |> List.fold_left(appReducer, InitialState.getInitialState());

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
  });

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

  describe("links", () => {
    test("should be added", () => {
      let finalState = [DialogOpen, AddLink, AddLink, AddLink] |> runActions;
      expect(finalState.dialogState.links |> List.length) |> toBe(3);
    });

    test("should not be possible to add more than 3 links", () => {
      let finalState =
        [DialogOpen, AddLink, AddLink, AddLink, AddLink] |> runActions;
      expect(finalState.dialogState.links |> List.length) |> toBe(3);
    });

    test("should not be possible to remove link if none exist", () => {
      let finalState = [DialogOpen, RemoveLink(0)] |> runActions;
      expect(finalState.dialogState.links |> List.length) |> toBe(0);
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
      expect(finalState.dialogState.links |> List.length) |> toBe(0);
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

      let changedLink = finalState.dialogState.links |> List.hd;
      expect((changedLink.text, changedLink.url))
      |> toEqual((linkText, linkUrl));
    });
  });
});
