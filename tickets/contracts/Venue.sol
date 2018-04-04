pragma solidity ^0.4.19;

import "./Ownable.sol";
import "./Event.sol";


contract Venue is Ownable {
    string public name;
    uint public price;

    Event[] public events;

    function addEvent(Event _event) public onlyOwner {
        events.push(_event);
    }
}
