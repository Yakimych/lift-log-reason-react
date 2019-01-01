/* State declaration */
type set = {
  reps: int,
  rpe: float,
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
  | Click
  | Toggle;

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
    dialogState: {
      isOpen: false,
      inputMode: SetsReps,
      numberOfRepsString: "5",
      numberOfReps: 5,
      numberOfSetsString: "5",
      numberOfSets: 5,
      customSetsStrings: [],
      customSets: [],
      commentIsShown: false,
      comment: "",
      canAddLink: true,
      links: [],
    },
  },

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Click =>
      ReasonReact.Update({
        ...state,
        dialogState: {
          ...state.dialogState,
          numberOfSets: state.dialogState.numberOfSets + 1,
        },
      })
    | Toggle =>
      ReasonReact.Update({...state, liftLogState: state.liftLogState})
    },

  render: self => {
    let message =
      "Number of log entries"
      ++ string_of_int(self.state.liftLogState.logEntries |> List.length);
    <div>
      <button onClick={_event => self.send(Click)}>
        {ReasonReact.string(message)}
      </button>
      <button onClick={_event => self.send(Toggle)}>
        {ReasonReact.string("Toggle test")}
      </button>
      {self.state.liftLogState.isLoading ?
         ReasonReact.string(testProp) : ReasonReact.null}
    </div>;
  },
};
