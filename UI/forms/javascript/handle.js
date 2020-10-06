function openCity(evt, cTabContent) {
    // Tab Control
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cTabContent).style.display = "block";
    evt.currentTarget.className += " active";

    let heightContent = document.getElementsByClassName(cTabContent).clientHeight;
    if (heightContent < 100) {
        document.getElementById(cTabContent).style.overflow = 'hidden';
    } else {
        document.getElementById(cTabContent).style.overflowY = 'scroll';
    }
}

// One of the Tab Show as Default
document.getElementById("defaultOpen").click();


let objNote = [];
let objSubtitle = [];
let noteTimeList = null;
let noteHighlightDuration = 5;

var wsUri = "ws://localhost:8081";//Localhost URL
var websocket = null;//Websocket variable
var dataString = "";//String containing retrieved data
var state = 0;//0 = get subtitles, 1 = subtitles recieved, get annotations



//load subtitles.txt -> this is called when the websocket returns data
function subtitleFile() {
    let content = document.getElementById('note');

    var lines = dataString.split('\n');
    for (var i = 0; i < lines.length - 1; i++) {
        // split Time
        var dPosition = lines[i].lastIndexOf(":");
        var time = lines[i].substring(0, dPosition);
        // Split Text
        var text = lines[i].substring(lines[i].lastIndexOf(':') + 1);

        var customObj = {
            te: text,
            ti: time,
        };
        objSubtitle.push(customObj);
    }
    objSubtitle.sort((a, b) => a.ti.localeCompare(b.ti));
    for (var i = 0; i < objSubtitle.length; i++) {
        content.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span>${objSubtitle[i].ti}</span>${objSubtitle[i].te}</p>`);
    }
    //Send annotations message
    state = 1;
    websocket.send("annotations.txt");
}

//load annotations.txt, this occurs when the second message is recieved
function annotationsTextFile() {
    let content = document.getElementById('transcript');

    var lines = dataString.split('\n');
    for (var i = 0; i < lines.length - 1; i++) {
        // split Time
        var dPosition = lines[i].lastIndexOf(":");
        var time = lines[i].substring(0, dPosition);
        // Split Text
        var text = lines[i].substring(lines[i].lastIndexOf(':') + 1);
        var customObj = {
            te: text,
            ti: time,
        };
        objNote.push(customObj);
    }
    objNote.sort((a, b) => a.ti.localeCompare(b.ti));
    for (var i = 0; i < objNote.length; i++) {
        content.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span class="noteTime">${objNote[i].ti}</span><span class="noteContent">${objNote[i].te}</span></p>`);
    }
    noteTimeList = document.querySelectorAll(".noteTime");

    //Closes web socket, gets are complete
    websocket.close();
}



document.addEventListener("DOMContentLoaded", function () {
    hiddenCircle();
    initWebSocket();
});


//This is where the websocket is initialized
function initWebSocket() {
    try {
        if (typeof MozWebSocket == 'function')
            WebSocket = MozWebSocket;
        if ( websocket && websocket.readyState == 1 )
            websocket.close();
        websocket = new WebSocket( wsUri );
        websocket.onopen = function (evt) {
            connect();
        };
        websocket.onmessage = function (evt) {
            handleData( evt.data );
        };
        websocket.onerror = function (evt) {
            // debug('ERROR: ' + evt.data);
        };
    } catch (exception) {
        debug('ERROR: ' + exception);
    }
}
//This is called when socket connects, sends the first get
function connect(){
    console.log("OPEN");
    websocket.send("subtitles.sub");
}

//Handle the returned data, call the correct method to display it
function handleData(message) {
    dataString = message;
    if(state == 0)
        subtitleFile();
    else
        annotationsTextFile();
}




document.addEventListener('click', function (event) {
    hiddenCircle();
    if (event.target.matches('#getid') || event.target.matches('span')) {
        let e = event.target;
        if (event.target.matches('span')) {
            e = event.target.parentNode;
        }
        event.preventDefault();
        if (e.closest('p')) {
            var currentTime = e.querySelector('span').innerText;
        }

        let circle = e.querySelector('i');
        circle.style.visibility = "visible";

        var a = currentTime.split(':');
        var seconds = (+a[0]) * 60 * 60 + (+a[1]) * 60 + (+a[2]);

        var player = document.getElementById("player");

        // check before Jumping which you put
        if (seconds > player.duration) {
            alert('invalid Time to Select')
        } else {
            player.currentTime = seconds;
            player.play();
            if (player.duration > 0 && !player.paused) {
                var str = document.getElementById('starter');
                str.classList.add('hide');

                player.addEventListener("timeupdate", function () {
                    const played = player.currentTime;
                    // console.log(played);
                    document.querySelector("#currentVideoTime").innerHTML = new Date(played * 1000).toISOString().substr(11, 8);
                    //const duration = player.duration.toFixed(1);
                    // document.querySelector("#currentVideoTime").innerHTML += "Zeit bis Ende " + (duration - played).toFixed(1);
                }, false);
            }
        }
    }

}, false);


// Notes highlight
const player = document.getElementById("player");
player.addEventListener("timeupdate", function () {
    const played = player.currentTime;
    for (let noteTime of noteTimeList) {
        let noteTimeNode = noteTime;
        noteTimeNode.parentNode.classList.remove("active");

        if (noteTimeNode.innerText <= formatSeconds(played)) {
            let difference = formatTime(formatSeconds(played)) - formatTime(noteTimeNode.innerText);

            if (difference <= noteHighlightDuration && difference >= 0) {
                noteTimeNode.parentNode.classList.add("active");
            }
        }
    }
}, false);

// Convert time to seconds format
function formatTime(hms) {
    let a = hms.split(':'); // split it at the colons

    // minutes are worth 60 seconds. Hours are worth 60 minutes.
    return (+a[0]) * 60 * 60 + (+a[1]) * 60 + (+a[2]);
}

// Convert seconds to time format
function formatSeconds(seconds)
{
    let date = new Date(1970,0,1);
    date.setSeconds(seconds);
    return date.toTimeString().replace(/.*(\d{2}:\d{2}:\d{2}).*/, "$1");
}

function hiddenCircle() {
    let circle = document.querySelectorAll('#getid i');
    circle.forEach(element => {
        element.style.visibility = "hidden";
    });
}




// objSubtitle
let isSub = true;
function subtitleSort() {
    var content1 = document.querySelector('#note');
    content1.innerHTML = '';
    content1.insertAdjacentHTML('afterbegin', `<div class="Order1"> <i class="fas fa-sort" onclick="subtitleSort()"></i> </div>`);

    if (isSub) {
        objSubtitle.sort((a, b) => b.ti.localeCompare(a.ti));
        for (var i = 0; i < objSubtitle.length; i++) {
            content1.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span>${objSubtitle[i].ti}</span>${objSubtitle[i].te}</p>`);
        }
        isSub = false;
    }
    else {
        objSubtitle.sort((a, b) => a.ti.localeCompare(b.ti));
        for (var i = 0; i < objSubtitle.length; i++) {
            content1.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span>${objSubtitle[i].ti}</span>${objSubtitle[i].te}</p>`);
        }
        isSub = true;
    }
}


// objNote
let isNote = true;
function transcriptSort() {
    let content = document.querySelector('#transcript');
    content.innerHTML = '';
    content.insertAdjacentHTML('afterbegin', `<div class="Order2"> <i class="fas fa-sort" onclick="transcriptSort()"></i> </div>`);
    if (isNote) {
        objNote.sort((a, b) => b.ti.localeCompare(a.ti));
        for (var i = 0; i < objNote.length; i++) {
            content.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span>${objNote[i].ti}</span>${objNote[i].te}</p>`);
        }
        isNote = false;
    }
    else {
        objNote.sort((a, b) => a.ti.localeCompare(b.ti));
        for (var i = 0; i < objNote.length; i++) {
            content.insertAdjacentHTML('beforeend', `<p id="getid"> <i class="circle"></i> <span>${objNote[i].ti}</span>${objNote[i].te}</p>`);
        }
        isNote = true;
    }
}






