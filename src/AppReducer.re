open AppActions;
open AppState;

let replaceLinkTextFunc = (newValue, oldValue) => {
  ...oldValue,
  text: newValue.text,
};
let replaceLinkUrlFunc = (newValue, oldValue) => {
  ...oldValue,
  url: newValue.url,
};

let appReducer = (action, state) =>
  switch (action) {
  | LogFetchStart =>
    ReasonReact.Update({
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: true,
        networkErrorOccured: false,
      },
    })
  | LogFetchSuccess(title) =>
    ReasonReact.Update({
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: false,
        networkErrorOccured: false,
        logTitle: title,
        errorMessage: None,
      },
      /* TODO: entries */
    })
  | LogFetchError(errorMessage) =>
    ReasonReact.Update({
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: false,
        networkErrorOccured: true,
        errorMessage: Some(errorMessage),
      },
    })
  | EntryChangeDate(newDate) =>
    ReasonReact.Update({
      ...state,
      newEntryState: {
        ...state.newEntryState,
        date: newDate,
      },
    })
  | EntryChangeName(newName) =>
    ReasonReact.Update({
      ...state,
      newEntryState: {
        ...state.newEntryState,
        name: newName,
      },
    })
  | EntryChangeWeightLifted(newWeightLiftedString) =>
    ReasonReact.Update({
      ...state,
      newEntryState: {
        ...state.newEntryState,
        weightLiftedString: newWeightLiftedString,
      },
      /* TODO: Parse string to float */
    })
  | DialogReset =>
    ReasonReact.Update({
      ...state,
      dialogState: InitialState.getInitialDialogState(),
    })
  | DialogOpen =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        isOpen: true,
      },
    })
  | DialogClose =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        isOpen: false,
      },
    })
  | SetInputMode(inputMode) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        inputMode,
      },
      /* TODO: Check if it's the first switch */
    })
  | SetNumberOfSets(numberOfSets) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfSetsString: numberOfSets,
      },
      /* Parse to float */
    })
  | SetNumberOfReps(numberOfReps) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfRepsString: numberOfReps,
      },
      /* Parse to float */
    })

  | AddCustomSet =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        customSets: state.dialogState.customSets @ [{reps: 5, rpe: None}],
      },
      /* TODO: Fetch the value of the last set */
      /* TODO: Check if another set can be added first */
    })
  | RemoveCustomSet(index) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        customSets:
          state.dialogState.customSets |> Utils.removeAtIndex(index),
        customSetsStrings:
          state.dialogState.customSetsStrings |> Utils.removeAtIndex(index),
      },
    })
  | ChangeCustomSet(index, newSetString) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        customSetsStrings:
          state.dialogState.customSetsStrings
          |> Utils.changeAtIndex(index, Utils.replaceFunc, newSetString),
      },
      /* TODO: customSets */
    })
  | ShowComment =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        commentIsShown: true,
      },
    })
  | ChangeComment(newComment) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        comment: newComment,
      },
    })
  | AddLink =>
    /* TODO: Check if link can be added first */
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        links: state.dialogState.links @ [{text: "text", url: "url"}],
      },
    })
  | RemoveLink(index) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        links: state.dialogState.links |> Utils.removeAtIndex(index),
      },
    })
  | ChangeLinkText(index, newText) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        links:
          state.dialogState.links
          |> Utils.changeAtIndex(
               index,
               replaceLinkTextFunc,
               {text: newText, url: ""},
             ),
      },
    })
  | ChangeLinkUrl(index, newUrl) =>
    ReasonReact.Update({
      ...state,
      dialogState: {
        ...state.dialogState,
        links:
          state.dialogState.links
          |> Utils.changeAtIndex(
               index,
               replaceLinkUrlFunc,
               {text: "", url: newUrl},
             ),
      },
    })
  };
