open AppState;
open BsReactstrap;

[%bs.raw {|require('./AddReps.css')|}];

let component = ReasonReact.statelessComponent("AddReps");

let make =
    (
      ~dialogState: dialogState,
      ~closeDialog,
      ~onInputModeChange,
      ~onAddCustomSet,
      ~onRemoveCustomSet,
      ~onCustomSetChange,
      ~onNumberOfSetsChange,
      ~onNumberOfRepsChange,
      ~addLink,
      ~removeLink,
      ~changeLinkText,
      ~changeLinkUrl,
      _children,
    ) => {
  ...component,
  render: _self => {
    <Modal isOpen={dialogState.isOpen} toggle=closeDialog>
      <ModalHeader> {ReasonReact.string("Input sets and reps")} </ModalHeader>
      <ModalBody>
        <div className="px-1">
          <div className="d-flex">
            <InputModeSwitch
              mode={dialogState.inputMode}
              onChange=onInputModeChange
            />
          </div>
          /* <div className="lead ml-4">
               {formatRepsSets(props.setsReps)}
             </div> */
          <div className="my-3">
            {dialogState.inputMode == SetsReps ?
               <SetsRepsInput
                 numberOfSets={dialogState.numberOfSetsString}
                 numberOfReps={dialogState.numberOfRepsString}
                 onNumberOfSetsChange
                 onNumberOfRepsChange
               /> :
               <CustomSetsInput
                 customSetsStrings={dialogState.customSetsStrings}
                 canAddSet=true
                 /* canAddSet={dialogState.canAddCustomSet} */
                 onAdd=onAddCustomSet
                 onRemove=onRemoveCustomSet
                 onChange=onCustomSetChange
               />}
          </div>
          <div className="d-flex flex-column align-items-start">
            <Links
              links={dialogState.links}
              addLink
              removeLink
              changeLinkText
              changeLinkUrl
            />
          </div>
        </div>
      </ModalBody>
      <ModalFooter>
        <Button color="primary"> {ReasonReact.string("Save")} </Button>
        <Button color="secondary" onClick=closeDialog>
          {ReasonReact.string("Cancel")}
        </Button>
      </ModalFooter>
    </Modal>;
  },
};
