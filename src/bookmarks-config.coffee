bookmarks: [
	{
		group: 'HACK'
		regexp: ///HA-?CK: (.*)///
		labelfx: (match) ->
			return "#{match[1]}"
	}
]
