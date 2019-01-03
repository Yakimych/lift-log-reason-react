open AppState;

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
