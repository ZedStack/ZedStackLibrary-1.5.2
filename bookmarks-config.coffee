bookmarks: [
	{
		group: "HACK"
		regexp: ///HACK: (.*)///i
		labelfx: (match)->
			return "#{match[1]}"
	}
]
