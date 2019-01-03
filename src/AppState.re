/* module AppState2 = { */
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
/* }; */
