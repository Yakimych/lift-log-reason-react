open AppState;

type action =
  /* | EntryAddStart
     | EntryAddSuccess
     | EntryAddError(string) */
  | ChangeDate(Js.Date.t)
  | ChangeName(string)
  | ChangeWeightLifted(string)
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
