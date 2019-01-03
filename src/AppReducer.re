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

let appReducerFunc = (state, action): appState =>
  switch (action) {
  | LogFetchStart => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: true,
        networkErrorOccured: false,
      },
    }
  | LogFetchSuccess(title) => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: false,
        networkErrorOccured: false,
        logTitle: title,
        errorMessage: None,
      },
      /* TODO: entries */
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
  | EntryChangeDate(newDate) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        date: newDate,
      },
    }
  | EntryChangeName(newName) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        name: newName,
      },
    }
  | EntryChangeWeightLifted(newWeightLiftedString) => {
      ...state,
      newEntryState: {
        ...state.newEntryState,
        weightLiftedString: newWeightLiftedString,
      },
      /* TODO: Parse string to float */
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
  | SetNumberOfSets(numberOfSets) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfSetsString: numberOfSets,
      },
      /* Parse to float */
    }
  | SetNumberOfReps(numberOfReps) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        numberOfRepsString: numberOfReps,
      },
      /* Parse to float */
    }

  | AddCustomSet => {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSets: state.dialogState.customSets @ [{reps: 5, rpe: None}],
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
  | ChangeCustomSet(index, newSetString) => {
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

let appReducer = (action, state) =>
  ReasonReact.Update(appReducerFunc(state, action));
