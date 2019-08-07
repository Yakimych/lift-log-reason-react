open AppState;

type action =
  | ChangeDate(Js.Date.t)
  | ChangeName(string)
  | ChangeWeightLifted(string)
  | FetchLogEntries(string)
  | ApiCallStarted
  | LogFetchSuccess(liftLog)
  | ApiCallError(string)
  | DialogReset
  | DialogOpen
  | DialogClose
  | ConfirmAddEntry(string)
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
