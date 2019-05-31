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

let maxNumberOfLinks = 3;
let maxNumberOfCustomSets = 30;

let canAddLink = dialogState => {
  dialogState.links |> List.length < maxNumberOfLinks;
};

let canAddCustomSet = dialogState => {
  dialogState.customSets |> List.length < maxNumberOfCustomSets;
};

let canRemoveCustomSet = dialogState => {
  dialogState.customSets |> List.length > 1;
};

let tryRemoveCustomSet = (index, dialogState) =>
  if (canRemoveCustomSet(dialogState)) {
    {
      ...dialogState,
      customSets: dialogState.customSets |> removeAtIndex(index),
      customSetsStrings:
        dialogState.customSetsStrings |> Utils.removeAtIndex(index),
    };
  } else {
    dialogState;
  };

let tryAddLink = dialogState =>
  if (canAddLink(dialogState)) {
    {
      ...dialogState,
      links: dialogState.links @ [{text: "text", url: "url"}],
    };
  } else {
    dialogState;
  };

let getCustomSetsFromSetsReps = dialogState => {
  let customSetsString =
    Array.make(dialogState.numberOfSets, dialogState.numberOfRepsString)
    |> Array.to_list;
  let customSets =
    Array.make(
      dialogState.numberOfSets,
      {reps: dialogState.numberOfReps, rpe: None},
    )
    |> Array.to_list;
  (customSets, customSetsString);
};

let appReducer = (state, action): appState =>
  switch (action) {
  | FetchLogEntries
  | AddLogEntry => {
      ...state,
      liftLogState: {
        ...state.liftLogState,
        isLoading: true,
        networkErrorOccured: false,
        errorMessage: None,
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
  | ApiCallError(errorMessage) => {
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
  | SetInputMode(inputMode) =>
    /* TODO: Refactor */
    let switchingToCustom = inputMode == CustomReps;
    let isFirstSwitch = state.dialogState.customSets |> List.length == 0;
    if (switchingToCustom && isFirstSwitch) {
      let (customSets, customSetsStrings) =
        getCustomSetsFromSetsReps(state.dialogState);
      {
        ...state,
        dialogState: {
          ...state.dialogState,
          customSets,
          customSetsStrings,
          inputMode,
        },
      };
    } else {
      {
        ...state,
        dialogState: {
          ...state.dialogState,
          inputMode,
        },
      };
    };
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
  | AddCustomSet =>
    if (!canAddCustomSet(state.dialogState)) {
      state;
    } else {
      let lastSet = state.dialogState.customSets |> List.rev |> List.hd;
      let lastSetString =
        state.dialogState.customSetsStrings |> List.rev |> List.hd;
      {
        ...state,
        dialogState: {
          ...state.dialogState,
          customSets: state.dialogState.customSets @ [lastSet],
          customSetsStrings:
            state.dialogState.customSetsStrings @ [lastSetString],
        },
      };
    }
  | RemoveCustomSet(index) => {
      ...state,
      dialogState: tryRemoveCustomSet(index, state.dialogState),
    }
  | ChangeCustomSet(index, newSetString) =>
    let newSet =
      index
      |> List.nth(state.dialogState.customSets)
      |> Belt.Option.getWithDefault(newSetString |> toValidSet);

    {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSetsStrings:
          state.dialogState.customSetsStrings
          |> changeAtIndex(index, replaceFunc, newSetString),
        customSets:
          state.dialogState.customSets
          |> changeAtIndex(index, replaceFunc, newSet),
      },
    };
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
  | AddLink => {...state, dialogState: tryAddLink(state.dialogState)}
  | RemoveLink(index) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        links: state.dialogState.links |> removeAtIndex(index),
      },
    }
  | ChangeLinkText(index, newText) => {
      ...state,
      dialogState: {
        ...state.dialogState,
        links:
          state.dialogState.links
          |> changeAtIndex(
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
          |> changeAtIndex(
               index,
               replaceLinkUrlFunc,
               {text: "", url: newUrl},
             ),
      },
    }
  };
