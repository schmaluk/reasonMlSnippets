let component = ReasonReact.statelessComponent("Modal");

let make = (~visible=false, _children) => {
  let myLabel: ReasonReact.reactElement =
    ReasonReact.cloneElement(
      <span />,
      ~props={"aria-hidden": "true"},
      [|Utils.str("&times;")|]
    );
  let myButton: ReasonReact.reactElement =
    ReasonReact.cloneElement(
      <button _type="button" className="close" />,
      ~props={"data-dismiss": "modal", "aria-label": "Close"},
      [|myLabel|]
    );
  {
    ...component,
    render: _self =>
      ReasonReact.cloneElement(
        <div
          className="modal modal-dialog-centered"
          id="exampleModal"
          role="dialog"
        />,
        ~props={"tabIndex": "-1", "aria-hidden": "true"},
        [|
          <div className="modal-dialog" role="document">
            <div className="modal-content">
              <div className="modal-header">
                <h5 className="modal-title"> (Utils.str("Modal title")) </h5>
                myButton
              </div>
              <div className="modal-body">
                <p> (Utils.str("Modal body text goes here.")) </p>
              </div>
              <div className="modal-footer">
                <button _type="button" className="btn btn-primary">
                  (Utils.str("Save changes"))
                </button>
                (
                  ReasonReact.cloneElement(
                    <button _type="button" className="btn btn-secondary" />,
                    ~props={"data-dismiss": "modal"},
                    [|Utils.str("Close")|]
                  )
                )
              </div>
            </div>
          </div>
        |]
      )
  };
};