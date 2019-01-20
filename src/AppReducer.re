open AppActions;
open AppState;
open Utils;

let replaceLinkTextFunc = (newValue, oldValue) => {
  ...oldValue,
  text: newValue.text,
};

let replaceLinkUrlFunc = (newValue, oldValue) => {
  ...oldValue,
  url: newValue.url,
};

let appReducer = (state, action): appState =>
  switch (action) {
  | LogFetchStart => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: true,
        networkErrorOccured: false,
      },
    }
  | LogFetchSuccess(liftLog) => {
      ...state,
      liftLogState: {
        isLoading: false,
        networkErrorOccured: false,
        logTitle: liftLog.title,
        logEntries: liftLog.entries,
        errorMessage: None,
      },
    }
  | LogFetchError(errorMessage) => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: false,
        networkErrorOccured: true,
        errorMessage: Some(errorMessage),
      },
    }
  /* TODO: Consolidate with Loading LiftLog? ApiRequestStart/Success/Error? */
  | EntryAddStart => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: true,
        networkErrorOccured: false,
        errorMessage: None,
      },
    }
  /* | EntryAddSuccess => {
       ...state,
       liftLogState: {
         ...state.liftLogState,
         isLoading: false,
         networkErrorOccured: false,
         errorMessage: None,
       },
     } */
  | EntryAddError(errorMessage) => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: false,
        networkErrorOccured: true,
        errorMessage: Some(errorMessage),
      },
    }
  | ChangeDate(newDate) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        date: newDate,
      },
    }
  | ChangeName(newName) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        name: newName,
      },
    }
  | ChangeWeightLifted(newWeightLiftedString) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        weightLiftedString: newWeightLiftedString,
        weightLifted:
          state.newEntryState.weightLifted
          |> Belt.Option.getWithDefault(newWeightLiftedString |> toMaybeFloat),
      },
    }
  | DialogReset => {
      ...state,
      dialogState: InitialState.getInitialDialogState(),
    }
  | DialogOpen => {
      ...state,
      dialogState: {
        ...state.dialogState,
        isOpen: true,
      },
    }
  | DialogClose => {
      ...state,
      dialogState: {
        ...state.dialogState,
        isOpen: false,
      },
    }
  | SetInputMode(inputMode) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        inputMode,
      },
      /* TODO: Check if it's the first switch */
    }
  | SetNumberOfSets(numberOfSetsString) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfSetsString,
        numberOfSets:
          state.dialogState.numberOfSets
          |> Belt.Option.getWithDefault(numberOfSetsString |> toMaybeInt),
      },
    }
  | SetNumberOfReps(numberOfRepsString) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfRepsString,
        numberOfReps:
          state.dialogState.numberOfReps
          |> Belt.Option.getWithDefault(numberOfRepsString |> toMaybeInt),
      },
    }

  | AddCustomSet => {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSets: state.dialogState.customSets @ [{reps: 5, rpe: None}],
        customSetsStrings: state.dialogState.customSetsStrings @ ["5"],
      },
      /* TODO: Fetch the value of the last set */
      /* TODO: Check if another set can be added first */
    }
  | RemoveCustomSet(index) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSets:
          state.dialogState.customSets |> Utils.removeAtIndex(index),
        customSetsStrings:
          state.dialogState.customSetsStrings |> Utils.removeAtIndex(index),
      },
    }
  | ChangeCustomSet(index, newSetString) =>
    /* let newSetValue =
         0 |> Belt.Option.getWithDefault(newSetString |> toMaybeInt);
       let newSet = index |> List.nth(state.dialogState.customSets); */

    {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSetsStrings:
          state.dialogState.customSetsStrings
          |> Utils.changeAtIndex(index, Utils.replaceFunc, newSetString),
      },
      /* TODO: customSets */
    }
  | ShowComment => {
      ...state,
      dialogState: {
        ...state.dialogState,
        commentIsShown: true,
      },
    }
  | ChangeComment(newComment) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        comment: newComment,
      },
    }
  | AddLink =>
    /* TODO: Check if link can be added first */
    {
      ...state,
      dialogState: {
        ...state.dialogState,
        links: state.dialogState.links @ [{text: "text", url: "url"}],
      },
    }
  | RemoveLink(index) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        links: state.dialogState.links |> Utils.removeAtIndex(index),
      },
    }
  | ChangeLinkText(index, newText) => {
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
    }
  | ChangeLinkUrl(index, newUrl) => {
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
    }
  };
