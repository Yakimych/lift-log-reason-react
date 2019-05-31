type set = {
  reps: int,
  rpe: option(float),
};

type liftInfoLink = {
  text: string,
  url: string,
};

type liftLogEntry = {
  date: Js.Date.t,
  name: string,
  weightLifted: float,
  sets: list(set),
  comment: string,
  links: list(liftInfoLink),
};

type liftLog = {
  name: string,
  title: string,
  entries: list(liftLogEntry),
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
  weightLifted: float,
};

type inputMode =
  | SetsReps
  | CustomReps;

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
  links: list(liftInfoLink) /* TODO: Change to array? */
};

type appState = {
  liftLogState,
  newEntryState,
  dialogState,
};
