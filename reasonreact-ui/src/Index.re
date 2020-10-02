// Entry point

// Force load css by importing required object
%raw
{|
import '@patternfly/react-core/dist/styles/base.css'
import { AboutModal, Button, TextContent, TextList, TextListItem } from '@patternfly/react-core';
|};

switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<App />, root)
| None => ()
};
