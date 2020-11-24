<template>
  <div>
	  <router-view />
  </div>
</template>

<script>
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


</style>
