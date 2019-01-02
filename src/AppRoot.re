/* State declaration */
type set = {
  reps: int,
  rpe: option(float),
};

type liftLogEntry = {
  date: Js.Date.t,
  name: string,
  weightLifted: float,
  sets: list(set),
};

type liftLogState = {
  isLoading: bool,
  networkErrorOccured: bool,
  errorMessage: option(string),
  logTitle: string,
  logEntries: list(liftLogEntry),
};

type newEntryState = {
  date: Js.Date.t,
  name: string,
  weightLiftedString: string,
  weightLifted: option(int),
};

type inputMode =
  | SetsReps
  | CustomReps;

type liftInfoLink = {
  text: string,
  url: string,
};

type dialogState = {
  isOpen: bool,
  inputMode,
  numberOfSetsString: string,
  numberOfSets: int,
  numberOfRepsString: string,
  numberOfReps: int,
  customSetsStrings: list(string),
  customSets: list(set),
  commentIsShown: bool,
  comment: string,
  canAddLink: bool,
  links: list(liftInfoLink),
};

type appState = {
  liftLogState,
  newEntryState,
  dialogState,
};

/* Action declaration */
type action =
  /* | EntryAddStart
     | EntryAddSuccess
     | EntryAddError(string) */
  | EntryChangeDate(Js.Date.t)
  | EntryChangeName(string)
  | EntryChangeWeightLifted(string)
  | LogFetchStart
  | LogFetchSuccess(string) /* TODO: LiftLog */
  | LogFetchError(string)
  | DialogReset
  | DialogOpen
  | DialogClose
  | SetInputMode(inputMode)
  | SetNumberOfSets(string)
  | SetNumberOfReps(string)
  | AddCustomSet
  | RemoveCustomSet(int)
  | ChangeCustomSet(int, string)
  | ShowComment
  | ChangeComment(string)
  | AddLink
  | RemoveLink(int)
  | ChangeLinkText(int, string)
  | ChangeLinkUrl(int, string);

let getInitialDialogState = () => {
  isOpen: false,
  inputMode: SetsReps,
  numberOfRepsString: "5",
  numberOfReps: 5,
  numberOfSetsString: "3",
  numberOfSets: 3,
  customSets: [
    {reps: 5, rpe: None},
    {reps: 5, rpe: None},
    {reps: 5, rpe: None},
  ],
  customSetsStrings: ["5", "5", "5"],
  commentIsShown: false,
  comment: "",
  canAddLink: true,
  links: [],
};

let removeAtIndex = (index, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.filter(t => t |> fst != index)
  |> List.map(t => t |> snd);

let changeAtIndex = (index, replaceFunc, newValue, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.map(t =>
       if (t |> fst == index) {
         t |> snd |> replaceFunc(newValue);
       } else {
         t |> snd;
       }
     );

let replaceFunc = (newValue, _) => newValue;
let replaceLinkTextFunc = (newValue, oldValue) => {
  ...oldValue,
  text: newValue.text,
};
let replaceLinkUrlFunc = (newValue, oldValue) => {
  ...oldValue,
  url: newValue.url,
};

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("AppRoot");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~testProp, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {
    liftLogState: {
      isLoading: true,
      networkErrorOccured: false,
      errorMessage: None,
      logTitle: "",
      logEntries: [],
    },
    newEntryState: {
      name: "",
      date: Js.Date.make(),
      weightLiftedString: "",
      weightLifted: None,
    },
    dialogState: getInitialDialogState(),
  },

  /* State transitions */
  reducer: (action, state) =>
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
      ReasonReact.Update({...state, dialogState: getInitialDialogState()})
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
          customSets: state.dialogState.customSets |> removeAtIndex(index),
          customSetsStrings:
            state.dialogState.customSetsStrings |> removeAtIndex(index),
        },
      })
    | ChangeCustomSet(index, newSetString) =>
      ReasonReact.Update({
        ...state,
        dialogState: {
          ...state.dialogState,
          customSetsStrings:
            state.dialogState.customSetsStrings
            |> changeAtIndex(index, replaceFunc, newSetString),
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
          links:
            state.dialogState.links
            @ [{text: "placeholderText", url: "placeholderUrl"}],
        },
      })
    | RemoveLink(index) =>
      ReasonReact.Update({
        ...state,
        dialogState: {
          ...state.dialogState,
          links: state.dialogState.links |> removeAtIndex(index),
        },
      })
    | ChangeLinkText(index, newText) =>
      ReasonReact.Update({
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
      })
    | ChangeLinkUrl(index, newUrl) =>
      ReasonReact.Update({
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
      })
    },

  render: self => {
    let numberOfLinksText =
      "Number of links: "
      ++ string_of_int(self.state.dialogState.links |> List.length);
    let links = self.state.dialogState.links;
    <div>
      <span> {ReasonReact.string(numberOfLinksText)} </span>
      <button onClick={_event => self.send(AddLink)}>
        {ReasonReact.string("Add link")}
      </button>
      {self.state.liftLogState.isLoading ?
         ReasonReact.string(testProp) : ReasonReact.null}
      <div>
        <ul>
          {links
           |> List.mapi((index, link) =>
                <li>
                  {ReasonReact.string(link.text ++ ": " ++ link.url)}
                  <div>
                    <input
                      value={link.text}
                      type_="text"
                      onChange={e =>
                        self.send(
                          ChangeLinkText(
                            index,
                            ReactEvent.Form.target(e)##value,
                          ),
                        )
                      }
                    />
                    <input
                      value={link.url}
                      type_="text"
                      onChange={e =>
                        self.send(
                          ChangeLinkUrl(
                            index,
                            ReactEvent.Form.target(e)##value,
                          ),
                        )
                      }
                    />
                    <button onClick={_ => self.send(RemoveLink(index))}>
                      {ReasonReact.string("X")}
                    </button>
                  </div>
                </li>
              )
           |> Array.of_list
           |> ReasonReact.array}
        </ul>
      </div>
    </div>;
  },
};
