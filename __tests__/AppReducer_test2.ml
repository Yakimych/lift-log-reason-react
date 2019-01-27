open Jest
open Expect
open AppReducer
open AppActions

let runActions actions =
  actions |> List.fold_left appReducer (InitialState.getInitialState())

let () =
  describe "AppReducer" (fun () ->
    describe "dialog" (fun () ->

      test "should be closed from the start" (fun () -> 
        let initialState = InitialState.getInitialState() in
        let dialogIsOpen = initialState.dialogState.isOpen in
        expect dialogIsOpen |> toBe false
      );

      test "should be open after DialogOpen is dispatched" (fun () -> 
        let finalState = [DialogClose; DialogOpen] |> runActions in
        let dialogIsOpen = finalState.dialogState.isOpen in
        expect dialogIsOpen |> toBe true
      );
    )
  )
