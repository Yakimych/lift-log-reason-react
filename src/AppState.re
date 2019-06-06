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
  sets: array(set),
  comment: string,
  links: array(liftInfoLink),
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
  | Standard
  | Custom;

type dialogState = {
  isOpen: bool,
  inputMode,
  numberOfSetsString: string,
  numberOfSets: int,
  numberOfRepsString: string,
  numberOfReps: int,
  customSetsStrings: array(string),
  customSets: array(set),
  commentIsShown: bool,
  comment: string,
  canAddLink: bool,
  links: array(liftInfoLink),
};

type appState = {
  liftLogState,
  newEntryState,
  dialogState,
};
