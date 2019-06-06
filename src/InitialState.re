open AppState;

let getInitialDialogState = () => {
  isOpen: false,
  inputMode: Standard,
  numberOfRepsString: "5",
  numberOfReps: 5,
  numberOfSetsString: "3",
  numberOfSets: 3,
  customSets: [||],
  customSetsStrings: [||],
  commentIsShown: false,
  comment: "",
  canAddLink: true,
  links: [||],
};

let getInitialLiftLogState = () => {
  isLoading: true,
  networkErrorOccured: false,
  errorMessage: None,
  logTitle: "",
  logEntries: [],
};

let getInitialNewEntryState = () => {
  name: "",
  date: Js.Date.make(),
  weightLiftedString: "",
  weightLifted: 0.0,
};

let getInitialState = () => {
  liftLogState: getInitialLiftLogState(),
  newEntryState: getInitialNewEntryState(),
  dialogState: getInitialDialogState(),
};
