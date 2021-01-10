module.exports = (mod) => {
    mod['extensions'] = {
        "getOwnPropertyNames": function(thing) {
            return Object.getOwnPropertyNames(thing);
        },
        "forEach": function(thing, callback) {
            for (let i in thing)
            {
                callback(i, thing[i]);
            }
        },
        "consolelog": function(thing) {
            console.log(thing);
        }
    }
}