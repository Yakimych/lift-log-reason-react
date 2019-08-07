open AppState;
open AppActions;
open BsReactstrap;

[%bs.raw {|require('./AddReps.css')|}];

let getDialogState = (state: appState) => state.dialogState;

[@react.component]
let make = (~logName: string) => {
  let dialogState = ElmishTest.useSelector(getDialogState);
  let dispatch = ElmishTest.useDispatch();

  <Modal
    isOpen={dialogState.isOpen}
    toggle={_ => dispatch(DialogClose)}
    backdrop="static">
    <ModalHeader> {ReasonReact.string("Input sets and reps")} </ModalHeader>
    <ModalBody>
      <div className="px-1">
        <div className="d-flex">
          <InputModeSwitch
            mode={dialogState.inputMode}
            onChange={mode => dispatch(SetInputMode(mode))}
          />
          <div className="lead ml-4">
            {Utils.formatDialogSetsReps(dialogState) |> ReasonReact.string}
          </div>
        </div>
        <div className="my-3">
          {dialogState.inputMode == Standard
             ? <SetsRepsInput
                 numberOfSets={dialogState.numberOfSetsString}
                 numberOfReps={dialogState.numberOfRepsString}
                 onNumberOfSetsChange={sets =>
                   dispatch(SetNumberOfSets(sets))
                 }
                 onNumberOfRepsChange={reps =>
                   dispatch(SetNumberOfReps(reps))
                 }
               />
             : <CustomSetsInput
                 customSetsStrings={dialogState.customSetsStrings}
                 canAddSet={AppReducer.canAddCustomSet(dialogState)}
                 onAdd={_ => dispatch(AddCustomSet)}
                 onRemove={index => dispatch(RemoveCustomSet(index))}
                 onChange={(index, stringValue) =>
                   dispatch(ChangeCustomSet(index, stringValue))
                 }
               />}
        </div>
        <div className="d-flex flex-column align-items-start">
          <Comment
            comment={dialogState.comment}
            hasComment={dialogState.commentIsShown}
            onCommentChange={c => dispatch(ChangeComment(c))}
            onOpenComment={_ => dispatch(ShowComment)}
          />
        </div>
        <Links
          links={dialogState.links}
          addLink={_ => dispatch(AddLink)}
          removeLink={index => dispatch(RemoveLink(index))}
          changeLinkText={(index, newText) =>
            dispatch(ChangeLinkText(index, newText))
          }
          changeLinkUrl={(index, newUrl) =>
            dispatch(ChangeLinkUrl(index, newUrl))
          }
        />
      </div>
    </ModalBody>
    <ModalFooter>
      <Button
        color="primary" onClick={_ => dispatch(ConfirmAddEntry(logName))}>
        {ReasonReact.string("Save")}
      </Button>
      <Button color="secondary" onClick={_ => dispatch(DialogClose)}>
        {ReasonReact.string("Cancel")}
      </Button>
    </ModalFooter>
  </Modal>;
};
