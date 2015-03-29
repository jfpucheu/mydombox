$(window).click(handleClick);

function handleClick(e) {
	var target = $(e.target).closest('a');
	if (target.attr('href')) {
		e.preventDefault();
		window.location = target.attr('href');
	}
}
