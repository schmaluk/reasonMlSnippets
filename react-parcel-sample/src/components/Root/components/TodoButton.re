

let component =  ReasonReact.statelessComponent("TodoButton");

let renderIcon = iconName => switch(iconName) {
    | Some(iconName)=> <i className={j|fa fa-$iconName pr-2|j} />
    | None => ReasonReact.nullElement
    };

let make = (~iconName=?, ~className="btn btn-primary", ~label, ~onClick, _children) => {
    ...component,
    render: (self) => (<button  
    className onClick>
    {renderIcon(iconName)}
    (Utils.str(label))
  </button>)
}