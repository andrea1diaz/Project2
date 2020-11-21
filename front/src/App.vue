<template>
  <div id="app">
	<SearchBar />
	<Result />
  </div>
</template>

<script>
	import SearchBar from '@/components/SearchBar'
	import Result from '@/components/Result'

export default {
  name: 'App',
  components: {
	SearchBar,
	Result
  }
}
</script>

<style>
body {
	background-color: #EAE4D8;
	margin: 0;
}

#app {
	font-family: Avenir, Helvetica, Arial, sans-serif;
	-webkit-font-smoothing: antialiased;
	-moz-osx-font-smoothing: grayscale;
	text-align: center;
	border: solid black 4px;
	border-radius: 15px;
	box-shadow: 5px 5px black;
	margin: 30px;
	height: -webkit-fill-available;
	width: -webkit-fill-available;
    position: fixed;
	overflow: hidden;
}


</style>
