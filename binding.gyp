{
    "targets": [
        {
            "target_name": "pafe",
            "sources": [ "pafe.cc" ],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")"
            ],
            "link_settings": {
                "libraries": [
                    "-lpafe", "-lusb"
                ]
            }
        }
    ],
}
