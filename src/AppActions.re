open AppState;

type action =
  | ChangeDate(Js.Date.t)
  | ChangeName(string)
  | ChangeWeightLifted(string)
  | AddLogEntry
  | FetchLogEntries
  | LogFetchSuccess(liftLog)
  | ApiCallError(string)
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
