function setup() {

}

function url() {
    var value = document.getElementById("esp-host-url").value;
    return value;
}

function fetch_light() {
    fetch(`${url()}/light-sensor`)
        .then(res => res.text())
        .then(value => {
            document.getElementById("light-value").innerHTML = value;
        })
        .catch(reason => {
            console.log(reason);
        })
}

function fetch_gas() {
    fetch(`${url()}/gas-sensor`)
        .then(res => res.text())
        .then(value => {
            document.getElementById("gas-value").innerHTML = value;
        })
        .catch(reason => {
            console.log(reason);
        })
}

function fetch_usonic() {
    fetch(`${url()}/ultra-sonic-sensor`)
        .then(res => res.json())
        .then(value => {
            document.getElementById("duration-value").innerHTML = value.duration;
            document.getElementById("distance-value").innerHTML = value.distance;
        })
        .catch(reason => {
            console.log(reason);
        })
}

function fetch_line() {
    fetch(`${url()}/line-sensor`)
        .then(res => res.text())
        .then(value => {
            document.getElementById("line-value").innerHTML = value;
            if(value == 0) {
                document.getElementById("line-spec").innerHTML = "White";
            } else {
                document.getElementById("line-spec").innerHTML = "Black";
            }
        })
        .catch(reason => {
            console.log(reason);
        })
}

function update(ms) {
    fetch_light();
    fetch_gas();
    fetch_usonic();
    fetch_line();
}

setInterval(update, 100);