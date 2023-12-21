/* HLS Video Player Component */

import Hls from "hls.js";

export default function HLS_Player(uri: string): HTMLVideoElement {
    let element = document.createElement('video');
    let hls = new Hls();
    hls.on(Hls.Events.MEDIA_ATTACHED, function() {
        console.log("hls.js and video bound!");
    });
    hls.on(Hls.Events.MANIFEST_PARSED, function(event, data) {
        console.log("manifest loaded, found " + data.levels.length + " quality level");
    });
    hls.loadSource(uri);
    hls.attachMedia(element);
    return element;
}
