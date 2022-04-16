/* rep(7,3) = [7,6,5] : the left part at floor 7th */
function rep (s,l) {
    return [...Array(l).keys()].map(x => s-x);
}

/* getFloorAt(7) = "7 6 5 4 5 6 7" */
function getFloorAt (level) {
    const halfLevel = level/2 - (level/2) % 1;
    const arr = rep(level, halfLevel);
    const brr = arr.slice().reverse();
    if (level % 2 != 0) {
        arr.push(level - halfLevel);
    }
    return arr.concat(brr).map(x => x%10).join(" ");
}

/* build pyramid */
function buildPyramid (scale) {
    let tempString = "";
    for (let i = 1; i <= scale; i++) {
        tempString += `<div class="logContent">${getFloorAt(i)}</div>`;
    }
    const pyramidField = document.getElementById("pyramid");
    pyramidField.innerHTML = tempString;
}

/* add click event listener */
const input = document.getElementById("input");
const submit = document.getElementById("submit");

function onClick (v) {
    const size = input.value;
    console.log(size);
    buildPyramid(size);
}
submit.addEventListener("click", onClick);