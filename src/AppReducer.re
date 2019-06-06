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

let canAddEntry = name => name |> String.length > 0;

let canAddLink = dialogState =>
  dialogState.links->Belt.Array.length < maxNumberOfLinks;

let canAddCustomSet = dialogState =>
  dialogState.customSets->Belt.Array.length < maxNumberOfCustomSets;

let canRemoveCustomSet = dialogState =>
  dialogState.customSets->Belt.Array.length > 1;

let tryRemoveCustomSet = (index, dialogState) =>
  if (canRemoveCustomSet(dialogState)) {
    {
      ...dialogState,
      customSets:
        dialogState.customSets
        ->Belt.Array.keepWithIndex((_, i) => i !== index),
      customSetsStrings:
        dialogState.customSetsStrings
        ->Belt.Array.keepWithIndex((_, i) => i !== index),
    };
  } else {
    dialogState;
  };

let tryAddLink = dialogState =>
  if (canAddLink(dialogState)) {
    {
      ...dialogState,
      links:
        dialogState.links->Belt.Array.concat([|{text: "text", url: "url"}|]),
    };
  } else {
    dialogState;
  };

let appReducer = (state, action): appState =>
  switch (action) {
  | ApiCallStarted => {
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
    let isFirstSwitch = state.dialogState.customSets->Belt.Array.length == 0;
    if (switchingToCustom && isFirstSwitch) {
      let customSetsStrings =
        Array.make(
          state.dialogState.numberOfSets,
          state.dialogState.numberOfRepsString,
        );
      let customSets = Utils.getSetsFromSetsReps(state.dialogState);

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
      let lastSet =
        state.dialogState.customSets
        ->Belt.Array.getExn(
            Belt.Array.length(state.dialogState.customSets) - 1,
          );
      let lastSetString =
        state.dialogState.customSetsStrings
        ->Belt.Array.getExn(
            Belt.Array.length(state.dialogState.customSets) - 1,
          );
      {
        ...state,
        dialogState: {
          ...state.dialogState,
          customSets:
            state.dialogState.customSets->Belt.Array.concat([|lastSet|]),
          customSetsStrings:
            state.dialogState.customSetsStrings
            ->Belt.Array.concat([|lastSetString|]),
        },
      };
    }
  | RemoveCustomSet(index) => {
      ...state,
      dialogState: tryRemoveCustomSet(index, state.dialogState),
    }
  | ChangeCustomSet(index, newSetString) =>
    let maybeValidSet = newSetString |> toValidSet;
    let newSet =
      maybeValidSet->Belt.Option.getWithDefault(
        Belt.Array.getExn(state.dialogState.customSets, index),
      );

    let newCustomSets = state.dialogState.customSets->Belt.Array.copy;
    newCustomSets->Belt.Array.setExn(index, newSet);

    let newCustomSetsStrings =
      state.dialogState.customSetsStrings->Belt.Array.copy;
    newCustomSetsStrings->Belt.Array.setExn(index, newSetString);

    {
      ...state,
      dialogState: {
        ...state.dialogState,
        customSetsStrings: newCustomSetsStrings,
        customSets: newCustomSets,
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
        links:
          state.dialogState.links
          ->Belt.Array.keepWithIndex((_, i) => i !== index),
      },
    }
  | ChangeLinkText(index, newText) =>
    // TODO: Extract into a function?
    let linkToReplace = state.dialogState.links->Belt.Array.getExn(index);
    let newLinks = Belt.Array.copy(state.dialogState.links);
    newLinks->Belt.Array.setExn(
      index,
      {text: newText, url: linkToReplace.url},
    );

    {
      ...state,
      dialogState: {
        ...state.dialogState,
        links: newLinks,
      },
    };
  | ChangeLinkUrl(index, newUrl) =>
    // TODO: Extract into a function?
    let linkToReplace = state.dialogState.links->Belt.Array.getExn(index);
    let newLinks = Belt.Array.copy(state.dialogState.links);
    newLinks->Belt.Array.setExn(
      index,
      {text: linkToReplace.text, url: newUrl},
    );

    {
      ...state,
      dialogState: {
        ...state.dialogState,
        links: newLinks,
      },
    };
  };
